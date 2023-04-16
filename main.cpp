#define default_type double
#define polyfit_max_degree 15
#define fft_peaks_number 5

#include "space.h"
#include "statistics.h"
#include "methods.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <filesystem>

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

template <unsigned int domain_size, unsigned int codomain_size>
bool get_function(const std::vector<std::vector<std::string>> &s_content, function<default_type, domain_size, codomain_size> &f)
{
    if (s_content.size() == 0)
        return false;

    if (s_content[0].size() != domain_size + codomain_size)
        return false;

    std::vector<std::vector<default_type>> d_content;
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        std::vector<default_type> d_cont;
        for (unsigned int j = 0; j < s_content[i].size(); j++)
        {
            default_type d = std::stod(s_content[i][j]);
            if (d == std::numeric_limits<default_type>::infinity())
                throw std::runtime_error("nan or infinity number");
            d_cont.push_back(d);
        }
        d_content.push_back(d_cont);
    }

    f.clear();
    for (unsigned int i = 0; i < d_content.size(); i++)
    {
        domain<default_type, domain_size> d;
        codomain<default_type, codomain_size> c;
        for (unsigned int j = 0; j < d_content[i].size(); j++)
        {
            if (j < domain_size)
                d.set(j, d_content[i][j]);
            if (j >= domain_size)
                c.set(j - domain_size, d_content[i][j]);
        }

        f.set(d, c);
    }

    return true;
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> get_functions(std::vector<std::string> &csv_files)
{
    std::sort(csv_files.begin(), csv_files.end());
    std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> fs;
    for (std::string file : csv_files)
    {
        std::cout << "File: " << file << std::endl;
        std::cout << "\tReading..." << std::endl;

        std::vector<std::string> axis;
        std::vector<std::vector<std::string>> s_content;
        if (!read_csv(file, s_content, axis))
            throw std::runtime_error("error on reading");
        if (axis.size() > domain_size + codomain_size)
            throw std::runtime_error("function a number of dimensions (" + std::to_string(domain_size + codomain_size) + ") not implemented");

        std::cout << "\tParsing..." << std::endl;
        function<default_type, domain_size, codomain_size> f;
        if (!get_function(s_content, f))
            throw std::runtime_error("error on parsing function");

        fs.push_back(std::make_tuple(file, f));
    }

    return fs;
}

int main(int argc, char *argv[])
{
    std::string path = ".";
    std::vector<std::string> csv_files = get_csv_files(path);
    if (csv_files.size() == 0)
        throw std::runtime_error("no csv file found");

    try
    {
        std::vector<std::tuple<std::string, function<default_type, 1, 1>>> fs = get_functions<1, 1>(csv_files);
        std::cout << std::setprecision(16);
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