#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>

#define DECIMAL

#ifdef DECIMAL
#define ddt double // Domain Default Type
#define cdt double // Codomain Default Type
#else
#define ddt unsigned long int
#define cdt unsigned long int
#endif

using pair = std::pair<ddt, cdt>;
using function = std::vector<pair>;
using domain = std::vector<ddt>;
using codomain = std::vector<cdt>;

// get domain vector of function
domain get_domain(const function &f)
{
    domain domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].first);

    return domain;
}

// get codomain vector of function
codomain get_codomain(const function &f)
{
    codomain codomain;
    for (unsigned int i = 0; i < f.size(); i++)
        codomain.push_back(f[i].second);

    return codomain;
}

// get a function from domain and codomain
function get_function(const domain &d, const codomain &c)
{
    if (d.size() != c.size())
        throw std::logic_error("domain and codomain have a different number of elements");

    function f;
    for (unsigned int i = 0; i < d.size(); i++)
        f.push_back(std::make_pair(d[i], c[i]));

    return f;
}

// compute the sample size
bool get_sampling(const function &f, ddt &sample_size)
{
    domain d = get_domain(f);
    sample_size = d[1] - d[0];
    for (unsigned int i = 0; i < d.size(); i++)
        if (sample_size != 0 && i > 0 && std::fabs(sample_size - (d[i] - d[i - 1]) > 100 * std::numeric_limits<ddt>::epsilon()))
            return false;

    return true;
}

// get a subset of a function
function get_interval(const function &f, const ddt &interval_start, const ddt &interval_size)
{
    domain d = get_domain(f);
}