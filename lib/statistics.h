#pragma once

#include <cmath>
#include <algorithm>

class statistics
{
private:
    static FDST _poly_val(const codomain &c, const FDST &x)
    {
        FDST y = 0;
        for (unsigned int i = 0; i < c.size(); i++)
            y += c[i] * std::pow(x, i);
        return y;
    }

    static FDST _avg(const domain &v)
    {
        FDST avg = 0;
        for (unsigned int i = 0; i < v.size(); i++)
            avg += v[i];

        return avg / ((FDST)v.size());
    }

public:
    static FDST get_r2(const domain &x, const  domain &y, const codomain &c)
    {
        FDST sSRes = 0;
        FDST sSTot = 0;
        FDST avg_y = _avg(y);
        for (unsigned int i = 0; i < x.size(); i++)
        {
            sSRes += std::pow(y[i] - _poly_val(c, x[i]), 2);
            sSTot += std::pow(y[i] - avg_y, 2);
        }

        return 1.0 - sSRes / sSTot;
    }

    static FDST max(const codomain &y)
    {
        FDST m = std::numeric_limits<FDST>::min();
        for (unsigned int i = 0; i < y.size(); i++)
            if (y[i] > m)
                m = y[i];
        return m;
    }
};