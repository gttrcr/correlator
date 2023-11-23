#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>
#include <array>

#define DECIMAL

#ifdef DECIMAL
#define FDST double // FDST (Function Default Scalar Type)
#else
#define FDST unsigned long int
#endif

using DT = FDST;                  // DT (Domain Type) is a FDST. In the future, DT will be std::vector<FDST> to manage scalar fields
using CT = FDST;                  // CT (Codomain Type) is a FDST
using PAIR = std::pair<DT, CT>;   // PAIR is a pair of DT and CT
using domain = std::vector<DT>;   // domain is the set of starting values of function
using codomain = std::vector<CT>; // codomain is the image set of domain

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
    domain _domain;
    codomain _codomain;

    inline unsigned int _get_decimal_places(const FDST &s) const
    {
        std::string s_str = std::to_string(s);
        unsigned int index = s_str.find('.');
        if (index < s_str.length())
            return s_str.length() - index - 1;
        else
            return 0;
    }

public:
    corr_function() = default;

    corr_function(const domain &d, const codomain &c)
    {
        assert(d.size() == c.size());

        for (unsigned int i = 0; i < d.size(); i++)
        {
            _domain.push_back(d[i]);
            _codomain.push_back(c[i]);
        }
    }

    corr_function(const std::vector<PAIR> &pair_vector)
    {
        for (unsigned int i = 0; i < pair_vector.size(); i++)
        {
            _domain.push_back(pair_vector[i].first);
            _codomain.push_back(pair_vector[i].second);
        }
    }

    domain get_domain() const
    {
        return _domain;
    }

    codomain get_codomain() const
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
        unsigned int decimal_places = _get_decimal_places(_domain[0]);
        sample_size = _domain[1] - _domain[0];
        for (unsigned int i = 0; i < size(); i++)
            if (sample_size != 0 && i > 0 && std::fabs(sample_size - (_domain[i] - _domain[i - 1]) > pow(10, -decimal_places)))
                return false;

        return true;
    }

    corr_function range(const unsigned int &begin, const unsigned int &end) const
    {
        corr_function f;
        f._domain.insert(f._domain.end(), _domain.begin() + begin, _domain.begin() + end);
        f._codomain.insert(f._codomain.end(), _codomain.begin() + begin, _codomain.begin() + end);

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
            if (_codomain[i] != 0)
                ret_f.push_back(_domain[i], f._codomain[i] / _codomain[i]);
        return ret_f;
    }
};