#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>

#define DECIMAL

#ifdef DECIMAL
#define FDST double // FDST (Function Default Scalar Type)
#else
#define FDST unsigned long int
#endif

using DT = FDST;                // DT (Domain Type) is a FDST. In the future, DT will be a vector of FDST (std::vector<FDST>)
using CT = FDST;                // CT (Codomain Type) is a FDST
using PAIR = std::pair<DT, CT>; // PAIR is a pair of DT and CT
// using corr_function = std::vector<PAIR>; // FUNTION is a vector of pair
using DOMAIN = std::vector<DT>;   // DOMAIN is the set of starting values of function
using CODOMAIN = std::vector<CT>; // CODOMAIN is the image set of DOMAIN

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
        _domain = domain;
        _codomain = codomain;
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

// get a function from domain and codomain
corr_function get_function(const DOMAIN &d, const CODOMAIN &c)
{
    if (d.size() != c.size())
        throw std::logic_error("domain and codomain have a different number of elements");

    corr_function f;
    for (unsigned int i = 0; i < d.size(); i++)
        f.push_back(std::make_pair(d[i], c[i]));

    return f;
}

// get a subset of a function
corr_function get_interval(const corr_function &f, const unsigned int &interval_start, const unsigned int &interval_size)
{
    DOMAIN d = f.get_domain();
    CODOMAIN c = f.get_codomain();
    DOMAIN interval_d = DOMAIN(d.begin() + interval_start, d.begin() + interval_start + interval_size);
    CODOMAIN interval_c = CODOMAIN(c.begin() + interval_start, c.begin() + interval_start + interval_size);
    return get_function(interval_d, interval_c);
}

unsigned int get_decimal_places(const FDST &s)
{
    std::string s_str = std::to_string(s);
    unsigned int index = s_str.find('.');
    if (index < s_str.length())
        return s_str.length() - index - 1;
    else
        return 0;
}

// compute the sample size
bool get_sampling(const corr_function &f, FDST &sample_size)
{
    DOMAIN d = f.get_domain();
    unsigned int decimal_places = get_decimal_places(d[0]);
    sample_size = d[1] - d[0];
    for (unsigned int i = 0; i < d.size(); i++)
        if (sample_size != 0 && i > 0 && std::fabs(sample_size - (d[i] - d[i - 1]) > pow(10, -decimal_places)))
            return false;

    return true;
}