#pragma once

#include "../function.h"

#include <iostream>

std::map<std::string, function> rotate(const std::map<std::string, function> &fs)
{
    std::map<std::string, function> rotated;
    for (unsigned int i = 0; i < fs.begin()->second.size(); i++)
    {
        ddt j = 0;
        for (const std::pair<std::string, function> p : fs)
            rotated[std::to_string(i)].push_back(pair(j++, p.second[i].first));
    }

    return rotated;
}