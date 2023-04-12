#pragma once

#include "space.h"
#include <math.h>
#include <algorithm>

template <unsigned int domain_size, unsigned int codomain_size>
T_SPACE avg(const function<domain_size, codomain_size> &f, const unsigned int &variable_position)
{
    T_SPACE sum = 0;
    for (unsigned int i = 0; i < f.size(); i++)
        sum += f.get(i, variable_position);
    return sum / (T_SPACE)f.size();
}

// T_SPACE pearson(const function<1, 1> &f)
//{
//     T_SPACE x_avg = avg(f, 0);
//     T_SPACE y_avg = avg(f, 1);
//     T_SPACE num = 0;
//     T_SPACE x_den = 0;
//     T_SPACE y_den = 0;
//     for (unsigned int i = 0; i < f.size(); i++)
//     {
//         num += (f.get(i, 0) - x_avg) * (f.get(i, 1) - y_avg);
//         x_den += pow(f.get(i, 0) - x_avg, 2);
//         y_den += pow(f.get(i, 1) - y_avg, 2);
//     }
//
//     return num / sqrt(x_den * y_den);
// }

template <unsigned int domain_size, unsigned int codomain_size>
T_SPACE pearson(const function<domain_size, codomain_size> &f1, const function<domain_size, codomain_size> &f2)
{
    if (f1.size() != f2.size())
        throw std::runtime_error("different codomain size");

    T_SPACE x_avg = avg(f1, 1);
    T_SPACE y_avg = avg(f2, 1);
    T_SPACE num = 0;
    T_SPACE x_den = 0;
    T_SPACE y_den = 0;
    for (unsigned int i = 0; i < f1.size(); i++)
    {
        num += (f1.get(i, 1) - x_avg) * (f2.get(i, 1) - y_avg);
        x_den += pow(f1.get(i, 1) - x_avg, 2);
        y_den += pow(f2.get(i, 1) - y_avg, 2);
    }

    return num / sqrt(x_den * y_den);
}

template <typename T>
std::vector<std::tuple<T, T>> peaks(const std::vector<std::tuple<T, T>> &vector, const unsigned int &number_of_peaks)
{
    std::vector<std::tuple<T, T>> cp(vector);

    // sort descending
    std::sort(cp.begin(), cp.end(), [](const std::tuple<T, T> &lhs, const std::tuple<T, T> &rhs)
              { return std::get<1>(lhs) > std::get<1>(rhs); });

    return std::vector<std::tuple<T, T>>(cp.begin(), cp.begin() + number_of_peaks);
}