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
bool get_function(const std::vector<std::vector<std::string>> &s_content, function<domain_size, codomain_size> &f)
{
    if (s_content.size() == 0)
        return false;

    if (s_content[0].size() != domain_size + codomain_size)
        return false;

    std::vector<std::vector<T_SPACE>> d_content;
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        std::vector<T_SPACE> d_cont;
        for (unsigned int j = 0; j < s_content[i].size(); j++)
        {
            T_SPACE d = std::stod(s_content[i][j]);
            if (d == std::numeric_limits<T_SPACE>::infinity())
                throw std::runtime_error("nan or infinity number");
            d_cont.push_back(d);
        }
        d_content.push_back(d_cont);
    }

    f.clear();
    for (unsigned int i = 0; i < d_content.size(); i++)
    {
        domain<domain_size> d;
        codomain<codomain_size> c;
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

int main()
{
    std::vector<std::string> csv_files;
    std::string path = ".";
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".csv")
        {
            csv_files.push_back(entry.path());
            std::cout << "Found " << entry.path() << std::endl;
        }
    }

    std::vector<function<1, 1>> fs;
    for (std::string file : csv_files)
    {
        std::cout << "File: " << file << std::endl;
        std::cout << "\tReading...";
        
        std::vector<std::string> axis;
        std::vector<std::vector<std::string>> s_content;
        if (!read_csv(file, s_content, axis))
            return -1;
        std::cout << "ok" << std::endl;
        
        std::cout << "\tParsing...";
        function<1, 1> f;
        if (!get_function(s_content, f))
            return -2;
        std::cout << "ok" << std::endl;

        fs.push_back(f);
    }

    std::cout << std::setprecision(16);
    std::cout << "Correlating...";
    if (!methods(fs))
        return -3;
    std::cout << "ok" << std::endl;
}