#pragma once

#include "utils.h"

#include <map>
#include <algorithm>

// from argc and argv, create arguments struct
std::map<std::string, std::vector<std::string>> get_cli(int argc, char *argv[])
{
    std::vector<std::string> args;
    for (unsigned int i = 0; i < (unsigned int)argc; i++)
    {
        std::vector<std::string> line = utils::split(argv[i], " ");
        args.insert(args.end(), line.begin(), line.end());
    }

    // remove empty entries
    args.erase(std::remove_if(args.begin(), args.end(), [](const std::string &s)
                              { return s.find(' ', 0); }));

    std::map<std::string, std::vector<std::string>> complete_args;
    for (unsigned int i = 0; i < args.size(); i++)
    {
        std::string command;
        if (args[i].find("-") == 0 || args[i].find("--") == 0)
        {
            command = args[i++];
            std::vector<std::string> args_v;
            for (; i < args.size(); i++)
            {
                if (args[i].find("-") != 0 && args[i].find("--") != 0)
                    args_v.push_back(args[i]);
                else
                {
                    i--;
                    break;
                }
            }

            complete_args[command] = args_v;
        }
    }

    return complete_args;
}