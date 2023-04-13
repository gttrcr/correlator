/*
#pragma once

#include "space.h"

#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>

struct scope
{
private:
    std::vector<std::tuple<std::string, std::vector<long_t_space>>> _scope;

public:
    void add(const std::string &scope_name, const std::vector<long_t_space> &scope_value)
    {
        _scope.push_back(std::make_tuple(scope_name, scope_value));
    }

    std::string get_key(unsigned int i)
    {
        return std::get<0>(_scope[i]);
    }

    std::vector<long_t_space> get_values(unsigned int i)
    {
        return std::get<1>(_scope[i]);
    }

    unsigned int size()
    {
        return _scope.size();
    }
};

struct results
{
private:
    std::vector<scope> _scopes;

public:
    void add(const std::string &scope_name, const std::vector<std::vector<long_t_space>> &scope_value)
    {
        for (unsigned int i = 0; i < scope_value.size(); i++)
        {
            scope s;
            s.add(scope_name, scope_value[i]);
            _scopes.push_back(s);
        }
    }

    bool save(const std::string &filename, const std::string &cols)
    {
        std::ofstream res(filename + ".csv");
        if (!res.is_open())
            throw std::runtime_error("cannot open results.csv file");
        res << cols << std::endl;
        for (unsigned int i = 0; i < _scopes.size(); i++)
        {
            for (unsigned int j = 0; j < _scopes[i].size(); j++)
            {
                res << _scopes[i].get_key(j) << ",";
                std::vector<long_t_space> vs = _scopes[i].get_values(j);
                for (unsigned int v = 0; v < vs.size(); v++)
                    res << std::setprecision(std::numeric_limits<long_t_space>::digits10) << vs[v] << ",";
                res << std::endl;
            }
        }

        res.close();
        _scopes.clear();

        return true;
    }
};
*/