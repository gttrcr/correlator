#define POLYFIT_MAX_DEGREE 10
#define FFT_PEAKS_NUMBER 5
#define DOM_CODOM_DIM 2

#include <iostream>

struct arguments
{
public:
    unsigned int port = 0;                                   // port for socket connection (-p)
    std::string input = ".";                                 // input single file or a folder (-i)
    std::string output = get_default_output();               // output folder for correlation from input (-o)
    std::string socket_output = get_default_socket_output(); // output folder for socket correlation (-s)

    // default port for socket connection
    unsigned int get_default_port()
    {
        return 39785;
    }

    // default output folder
    std::string get_default_output()
    {
        return "out_correlator";
    }

    // default socket output folder
    std::string get_default_socket_output()
    {
        return "socket_out_correlator";
    }
};

#include "function.h"

#include "analysis/methods.h"

#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <regex>

// #include <netinet/in.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #define PORT 8080

// get the list of all csv files inside the folder
std::vector<std::string> get_csv_files(const std::string &path)
{
    std::vector<std::string> csv_files;
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".csv")
        {
            std::string filename = std::filesystem::path(entry.path()).string();
            csv_files.push_back(filename);
            std::cout << "Found " << filename << std::endl;
        }
    }

    return csv_files;
}

// read a csv file returning content and the list of axis
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

// return a function from content
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

// return all functions from csv filename
std::map<std::string, function> get_functions(const std::vector<std::string> &const_csv_files)
{
    std::vector<std::string> csv_files(const_csv_files);
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
            throw std::logic_error("function with a number of dimensions " + std::to_string(DOM_CODOM_DIM) + " not implemented");

        std::cout << "\tParsing..." << std::endl;
        function f;
        if (!get_function(s_content, f))
            throw std::runtime_error("error on parsing function");

        fs[std::filesystem::path(file).filename().string()] = f;
    }

    return fs;
}

// void socket_server()
// {
//     int server_fd, new_socket, valread;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char buffer[1024] = {0};
//     char *hello = "Hello from server";

//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Forcefully attaching socket to the port 8080
//     if (setsockopt(server_fd, SOL_SOCKET,
//                    SO_REUSEADDR | SO_REUSEPORT, &opt,
//                    sizeof(opt)))
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Forcefully attaching socket to the port 8080
//     if (bind(server_fd, (struct sockaddr *)&address,
//              sizeof(address)) < 0)
//     {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }
//     if (listen(server_fd, 3) < 0)
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }
//     if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
//                              (socklen_t *)&addrlen)) < 0)
//     {
//         perror("accept");
//         exit(EXIT_FAILURE);
//     }
//     valread = read(new_socket, buffer, 1024);
// }

inline std::vector<std::string> split(const std::string &s, const std::string &str_of_delimiters)
{
    std::regex re(str_of_delimiters);
    std::sregex_token_iterator first{s.begin(), s.end(), re, -1}, last;
    std::vector<std::string> tokens{first, last};

    return tokens;
}

arguments get_arguments(int argc, char *argv[])
{
    std::vector<std::string> args;
    for (unsigned int i = 0; i < (unsigned int)argc; i++)
    {
        std::vector<std::string> line = split(argv[i], " ");
        args.insert(args.end(), line.begin(), line.end());
    }

    // remove empty entries
    args.erase(std::remove_if(args.begin(), args.end(), [](const std::string &s)
                              { return s.find(' ', 0); }));

    std::map<std::string, std::vector<std::string>> complete_args;
    for (unsigned int i = 0; i < args.size(); i++)
    {
        std::string command;
        if (args[i].find("-") == 0)
        {
            command = args[i++];
            for (; i < args.size(); i++)
            {
                if (args[i].find("-") != 0)
                    complete_args[command].push_back(args[i]);
                else
                {
                    if (complete_args[command].size() == 0)
                        complete_args[command].push_back("");

                    i--;
                    break;
                }
            }

            if (complete_args[command].size() == 0)
                complete_args[command].push_back("");
        }
    }

    arguments a;
    for (const auto &pair : complete_args)
    {
        if (pair.first == "-p")
        {
            if (pair.second.size() == 1 && pair.second[0].empty())
                a.port = a.get_default_port();
            else if (pair.second.size() == 1 && !pair.second[0].empty() && std::find_if(pair.second[0].begin(), pair.second[0].end(), [](unsigned char c)
                                                                                        { return !std::isdigit(c); }) == pair.second[0].end())
                a.port = std::stoi(pair.second[0]);
        }

        if (pair.first == "-i" && pair.second.size() == 1 && !pair.second[0].empty())
            a.input = pair.second[0];

        if (pair.first == "-o" && pair.second.size() == 1 && !pair.second[0].empty())
            a.output = pair.second[0];
        else
            a.output = a.get_default_output();

        if (pair.first == "-s" && pair.second.size() == 1 && !pair.second[0].empty())
            a.socket_output = pair.second[0];
        else
            a.socket_output = a.get_default_socket_output();
    }

    return a;
}

void correlate_from_files(const std::vector<std::string> &csv_files, const arguments &args)
{
    try
    {
        std::map<std::string, function> fs = get_functions(csv_files);
        std::cout << "correlate from files..." << std::endl;
        analysis::all_methods(fs, args);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...)
    {
        std::cout << "generic error" << std::endl;
    }
}

void correlate_from_socket(const arguments &args)
{
}

int main(int argc, char *argv[])
{
    arguments args = get_arguments(argc, argv);

    std::vector<std::string> csv_files = get_csv_files(args.input);
    if (csv_files.size() > 0)
        correlate_from_files(csv_files, args);

    if (args.port != 0)
        correlate_from_socket(args);
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