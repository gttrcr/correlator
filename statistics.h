#pragma once

#include <cmath>
#include <algorithm>

class statistics
{
private:
    static default_type _poly_val(const std::vector<default_type> &c, const default_type &x)
    {
        default_type y = 0;
        for (unsigned int i = 0; i < c.size(); i++)
            y += c[i] * std::pow(x, i);
        return y;
    }

    static default_type _avg(const std::vector<default_type> &v)
    {
        default_type avg;
        for (unsigned int i = 0; i < v.size(); i++)
            avg += v[i];

        return avg / ((default_type)v.size());
    }

public:
    static default_type get_r2(const std::vector<default_type> &x, const std::vector<default_type> &y, const std::vector<default_type> &c)
    {
        default_type sSRes = 0;
        default_type sSTot = 0;
        default_type avg_y = _avg(y);
        for (unsigned int i = 0; i < x.size(); i++)
        {
            sSRes += std::pow(y[i] - _poly_val(c, x[i]), 2);
            sSTot += std::pow(y[i] - avg_y, 2);
        }

        return 1.0 - sSRes / sSTot;
    }

    static default_type max(const std::vector<default_type> &x)
    {
        default_type m = std::numeric_limits<default_type>::min();
        for (unsigned int i = 0; i < x.size(); i++)
            if (x[i] > m)
                m = x[i];
        return m;
    }

    // template <unsigned int domain_dim, unsigned int codomain_dim>
    // static default_type avg(const function<domain_dim, codomain_dim> &f, const unsigned int &variable_position)
    //{
    //     default_type sum = 0;
    //     for (unsigned int i = 0; i < f.size(); i++)
    //         sum += f.get(i, variable_position);
    //     return sum / (default_type)f.size();
    // }
    //
    // template <unsigned int domain_dim, unsigned int codomain_dim>
    // static default_type pearson(const function<domain_dim, codomain_dim> &f1, const function<domain_dim, codomain_dim> &f2)
    //{
    //    if (f1.size() != f2.size())
    //        throw std::runtime_error("different codomain size");
    //
    //    default_type x_avg = avg(f1, 1);
    //    default_type y_avg = avg(f2, 1);
    //    default_type num = 0;
    //    default_type x_den = 0;
    //    default_type y_den = 0;
    //    for (unsigned int i = 0; i < f1.size(); i++)
    //    {
    //        num += (f1.get(i, 1) - x_avg) * (f2.get(i, 1) - y_avg);
    //        x_den += pow(f1.get(i, 1) - x_avg, 2);
    //        y_den += pow(f2.get(i, 1) - y_avg, 2);
    //    }
    //
    //    return num / sqrt(x_den * y_den);
    //}
};