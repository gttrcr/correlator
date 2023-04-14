#pragma once

#include "space.h"
#include <cmath>
#include <algorithm>

template <unsigned int domain_size, unsigned int codomain_size>
default_type avg(const function<default_type, domain_size, codomain_size> &f, const unsigned int &variable_position)
{
    default_type sum = 0;
    for (unsigned int i = 0; i < f.size(); i++)
        sum += f.get(i, variable_position);
    return sum / (default_type)f.size();
}

template <unsigned int domain_size, unsigned int codomain_size>
default_type pearson(const function<default_type, domain_size, codomain_size> &f1, const function<default_type, domain_size, codomain_size> &f2)
{
    if (f1.size() != f2.size())
        throw std::runtime_error("different codomain size");

    default_type x_avg = avg(f1, 1);
    default_type y_avg = avg(f2, 1);
    default_type num = 0;
    default_type x_den = 0;
    default_type y_den = 0;
    for (unsigned int i = 0; i < f1.size(); i++)
    {
        num += (f1.get(i, 1) - x_avg) * (f2.get(i, 1) - y_avg);
        x_den += pow(f1.get(i, 1) - x_avg, 2);
        y_den += pow(f2.get(i, 1) - y_avg, 2);
    }

    return num / sqrt(x_den * y_den);
}