#pragma once

#include <cmath>
#include <algorithm>

class statistics
{
private:
    static cdt _poly_val(const std::vector<cdt> &c, const ddt &x)
    {
        cdt y = 0;
        for (unsigned int i = 0; i < c.size(); i++)
            y += c[i] * std::pow(x, i);
        return y;
    }

    static cdt _avg(const std::vector<cdt> &v)
    {
        cdt avg;
        for (unsigned int i = 0; i < v.size(); i++)
            avg += v[i];

        return avg / ((cdt)v.size());
    }

public:
    static cdt get_r2(const std::vector<ddt> &x, const std::vector<ddt> &y, const std::vector<cdt> &c)
    {
        cdt sSRes = 0;
        cdt sSTot = 0;
        cdt avg_y = _avg(y);
        for (unsigned int i = 0; i < x.size(); i++)
        {
            sSRes += std::pow(y[i] - _poly_val(c, x[i]), 2);
            sSTot += std::pow(y[i] - avg_y, 2);
        }

        return 1.0 - sSRes / sSTot;
    }

    static cdt max(const std::vector<cdt> &y)
    {
        cdt m = std::numeric_limits<cdt>::min();
        for (unsigned int i = 0; i < y.size(); i++)
            if (y[i] > m)
                m = y[i];
        return m;
    }
};