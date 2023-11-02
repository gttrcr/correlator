#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>

#define DECIMAL

#ifdef DECIMAL
#define FDST double // FDST (Function Default Scalar Type)
#else
#define FDST unsigned long int
#endif

using DT = FDST;                  // DT (Domain Type) is a FDST. In the future, DT will be std::vector<FDST> to manage scalar fields
using CT = FDST;                  // CT (Codomain Type) is a FDST
using PAIR = std::pair<DT, CT>;   // PAIR is a pair of DT and CT
using DOMAIN = std::vector<DT>;   // DOMAIN is the set of starting values of function
using CODOMAIN = std::vector<CT>; // CODOMAIN is the image set of DOMAIN

unsigned int get_decimal_places(const FDST &s)
{
    std::string s_str = std::to_string(s);
    unsigned int index = s_str.find('.');
    if (index < s_str.length())
        return s_str.length() - index - 1;
    else
        return 0;
}

/*
Example of a function
function =
{
    (ddt11 ddt12 ddt13 ... ddt... | dct1) => every row is a pair
    (ddt21 ddt22 ddt23 ... ddt...) => every first element if a dt (domain type)  | dct2
    ddt31 ddt32 ddt33 ... ddt... | (dct3) => every second element is a ct (codomain type)
    ...
    (ddt...1) => every single element is a   ddt...2 ddt...3 ... ddt...... | dct...
}
*/

class corr_function
{
private:
    DOMAIN _domain;
    CODOMAIN _codomain;

public:
    corr_function() = default;

    corr_function(const DOMAIN &domain, const CODOMAIN &codomain)
    {
        assert(domain.size() == codomain.size());

        unsigned int min = std::min(domain.size(), codomain.size());
        _domain = DOMAIN(domain.begin(), domain.begin() + min);
        _codomain = CODOMAIN(codomain.begin(), codomain.begin() + min);
    }

    corr_function(const std::vector<PAIR> &pair_vector)
    {
        for (unsigned int i = 0; i < pair_vector.size(); i++)
        {
            _domain.push_back(pair_vector[i].first);
            _codomain.push_back(pair_vector[i].second);
        }
    }

    DOMAIN get_domain() const
    {
        return _domain;
    }

    CODOMAIN get_codomain() const
    {
        return _codomain;
    }

    unsigned int size() const
    {
        return _domain.size();
    }

    void push_back(const DT &domain, const CT &codomain)
    {
        _domain.push_back(domain);
        _codomain.push_back(codomain);
    }

    PAIR operator[](const unsigned int &i) const
    {
        return PAIR(_domain[i], _codomain[i]);
    }

    // compute the sample size
    bool get_sampling(FDST &sample_size) const
    {
        unsigned int decimal_places = get_decimal_places(_domain[0]);
        sample_size = _domain[1] - _domain[0];
        for (unsigned int i = 0; i < size(); i++)
            if (sample_size != 0 && i > 0 && std::fabs(sample_size - (_domain[i] - _domain[i - 1]) > pow(10, -decimal_places)))
                return false;

        return true;
    }

    corr_function range(const unsigned int &begin, const unsigned int &end) const
    {
        corr_function f;
        for (unsigned int i = begin; i < end; i++)
            f.push_back(_domain[i], _codomain[i]);

        return f;
    }

    corr_function operator+(const corr_function &f) const
    {
        corr_function ret_f;
        for (unsigned int i = 0; i < f.size(); i++)
            ret_f.push_back(_domain[i], f._codomain[i] + _codomain[i]);
        return ret_f;
    }

    corr_function operator-(const corr_function &f) const
    {
        corr_function ret_f;
        for (unsigned int i = 0; i < f.size(); i++)
            ret_f.push_back(_domain[i], f._codomain[i] - _codomain[i]);
        return ret_f;
    }

    corr_function operator*(const corr_function &f) const
    {
        corr_function ret_f;
        for (unsigned int i = 0; i < f.size(); i++)
            ret_f.push_back(_domain[i], f._codomain[i] * _codomain[i]);
        return ret_f;
    }

    corr_function operator/(const corr_function &f) const
    {
        corr_function ret_f;
        for (unsigned int i = 0; i < f.size(); i++)
            ret_f.push_back(_domain[i], f._codomain[i] / _codomain[i]);
        return ret_f;
    }
};

// // get domain vector of function
// DOMAIN get_domain(const corr_function &f)
// {
//     DOMAIN domain;
//     for (unsigned int i = 0; i < f.size(); i++)
//         domain.push_back(f[i].first);

//     return domain;
// }

// // get codomain vector of function
// CODOMAIN get_codomain(const corr_function &f)
// {
//     CODOMAIN codomain;
//     for (unsigned int i = 0; i < f.size(); i++)
//         codomain.push_back(f[i].second);

//     return codomain;
// }

// // get a function from domain and codomain
// corr_function get_function(const DOMAIN &d, const CODOMAIN &c)
// {
//     if (d.size() != c.size())
//         throw std::logic_error("domain and codomain have a different number of elements");

//     corr_function f;
//     for (unsigned int i = 0; i < d.size(); i++)
//         f.push_back(d[i], c[i]);

//     return f;
// }

// // get a subset of a function
// corr_function get_interval(const corr_function &f, const unsigned int &interval_start, const unsigned int &interval_size)
// {
//     DOMAIN d = f.get_domain();
//     CODOMAIN c = f.get_codomain();
//     DOMAIN interval_d = DOMAIN(d.begin() + interval_start, d.begin() + interval_start + interval_size);
//     CODOMAIN interval_c = CODOMAIN(c.begin() + interval_start, c.begin() + interval_start + interval_size);
//     return corr_function(interval_d, interval_c);
// }