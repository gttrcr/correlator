#pragma once

#include "function.h"

#include <map>
#include <vector>
#include <regex>

namespace utils
{
    inline std::vector<std::string> split(const std::string &s, const std::string &str_of_delimiters)
    {
        std::regex re(str_of_delimiters);
        std::sregex_token_iterator first{s.begin(), s.end(), re, -1}, last;
        std::vector<std::string> tokens{first, last};

        return tokens;
    }

    inline bool is_integer(const std::string &str)
    {
        return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c)
                                            { return !std::isdigit(c); }) == str.end();
    }

    // transform a vector of template typename T to a vector of double
    template <typename T>
    static std::vector<double> to_double(const std::vector<T> &v)
    {
        std::vector<double> ret;
        for (unsigned int i = 0; i < v.size(); i++)
            ret.push_back((double)v[i]);

        return ret;
    }

    // rotate the map string-function to a map where function has domain accross functions
    // A={{1, 1}, {1.5, 3}, {2, 5}, {2.5, 7}}
    // B={{1, 14}, {1.5, 21}, {2, 24}, {2.5, 25}}
    // become
    // 1={{1, 1}, {2, 1}}
    // 2={{1, 3}, {2, 21}}
    // 3={{1, 5}, {2, 24}}
    // 4={{1, 7}, {2, 25}}
    std::map<std::string, corr_function> rotate(const std::map<std::string, corr_function> &fs)
    {
        std::map<std::string, corr_function> rotated;
        for (unsigned int i = 0; i < fs.begin()->second.size(); i++)
        {
            FDST j = 0;
            for (const std::pair<std::string, corr_function> p : fs)
                rotated[std::to_string(i)].push_back(j++, p.second[i].first);
        }

        return rotated;
    }
}