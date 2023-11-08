#pragma once

#include "function.h"

#include <map>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>

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

    inline bool is_number(const std::string &str)
    {
        char *end = nullptr;
        double val = strtod(str.c_str(), &end);
        return end != str.c_str() && *end == '\0' && val != HUGE_VAL;
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                        { return !std::isspace(ch); }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                             { return !std::isspace(ch); })
                    .base(),
                s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s)
    {
        rtrim(s);
        ltrim(s);
    }
}