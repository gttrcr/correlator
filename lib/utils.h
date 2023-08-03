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
}