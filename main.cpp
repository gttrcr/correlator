#include "function.h"

#include "analysis/polyfit.h"
#include "analysis/fft.h"
#include "analysis/peaks_migration.h"
#include "analysis/seeker.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <filesystem>
#include <map>

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

std::vector<std::string> get_csv_files(const std::string &path)
{
    std::vector<std::string> csv_files;
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".csv")
        {
            std::string filename = std::filesystem::path(entry.path()).filename().string();
            csv_files.push_back(filename);
            std::cout << "Found " << filename << std::endl;
        }
    }

    return csv_files;
}

bool read_csv(const std::string &fname, std::vector<std::vector<std::string>> &s_content, std::vector<std::string> &axis)
{
    s_content.clear();
    axis.clear();

    std::vector<std::string> row;
    std::fstream file(fname, std::ios::in);
    if (file.is_open())
    {
        bool first = true;
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "")
                continue;

            row.clear();
            std::stringstream str(line);
            std::string word;
            while (std::getline(str, word, ','))
            {
                word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
                word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
                word.erase(std::remove(word.begin(), word.end(), '\t'), word.end());

                if (first)
                    axis.push_back(word);
                else
                    row.push_back(word);
            }

            if (!first)
                s_content.push_back(row);

            if (first)
                first = false;
        }

        return true;
    }

    return false;
}

bool get_function(const std::vector<std::vector<std::string>> &s_content, function &f)
{
    if (s_content.size() == 0)
        return false;

    if (s_content[0].size() != DOM_CODOM_DIM)
        return false;

    f.clear();
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        if (s_content[i].size() > 1)
        {
            for (unsigned int j = 0; j < s_content[i].size(); j++)
            {
                cdt d = std::stod(s_content[i][j]);
                if (d == std::numeric_limits<cdt>::infinity())
                    throw std::runtime_error("nan or infinity number");
            }
        }
        else
            throw std::runtime_error("the function has dimension less than 2");

        f.push_back(pair(std::stod(s_content[i][0]), std::stod(s_content[i][1])));
    }

    return true;
}

std::map<std::string, function> get_functions(std::vector<std::string> &csv_files)
{
    std::sort(csv_files.begin(), csv_files.end());
    std::map<std::string, function> fs;
    for (std::string file : csv_files)
    {
        std::cout << "File: " << file << std::endl;
        std::cout << "\tReading..." << std::endl;

        std::vector<std::string> axis;
        std::vector<std::vector<std::string>> s_content;
        if (!read_csv(file, s_content, axis))
            throw std::runtime_error("error on reading");
        if (axis.size() > DOM_CODOM_DIM)
            throw std::runtime_error("function a number of dimensions " + std::to_string(DOM_CODOM_DIM) + " not implemented");

        std::cout << "\tParsing..." << std::endl;
        function f;
        if (!get_function(s_content, f))
            throw std::runtime_error("error on parsing function");

        fs[file] = f;
    }

    return fs;
}

void methods(const std::map<std::string, function> &fs)
{
    std::filesystem::create_directory("output");

    // compute best polynomial fit
    std::cout << "polyfit..." << std::endl;
    for (const std::pair<std::string, function> f : fs)
        polyfit::compute(f.second, polyfit_max_degree, "polyfit_" + std::filesystem::path(f.first).stem().string());
    if (fs.size() > 1)
        polyfit::compute(fs, polyfit_max_degree, "polyfit");

    // compute fft of vector of fs and return their peaks
    std::cout << "fft" << std::endl;
    std::map<std::string, function> spectra = fft::compute(fs);

    // get peaks
    std::cout << "peaks..." << std::endl;
    std::map<std::string, function> peaks = fft::get_peaks(spectra, fft_peaks_number);

    // peaks migration
    std::cout << "peaks polyfit..." << std::endl;
    std::map<std::string, function> rotated_peaks = rotate(peaks);
    for (const std::pair<std::string, function> f : rotated_peaks)
        polyfit::compute(f.second, f.second.size(), "peak_migr" + std::filesystem::path(f.first).stem().string());

#ifdef INTEGERS
    seeker::compute();
#endif
}

void socket_server()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
}

int main(int argc, char *argv[])
{
    //socket_server();
    std::string path = ".";
    std::vector<std::string> csv_files = get_csv_files(path);
    if (csv_files.size() == 0)
        throw std::runtime_error("no csv file found");

    try
    {
        std::map<std::string, function> fs = get_functions(csv_files);
        std::cout << "Correlating..." << std::endl;
        methods(fs);
        std::cout << "Done" << std::endl;

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    catch (...)
    {
        std::cout << "generic error" << std::endl;
        return -1;
    }
}

/*
// Server side C/C++ program to demonstrate Socket
// programming
int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                SO_REUSEADDR | SO_REUSEPORT, &opt,
                sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
            sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
        = accept(server_fd, (struct sockaddr*)&address,
                (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
*/