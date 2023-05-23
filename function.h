#pragma once

#include <vector>
#include <iostream>

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

domain get_domain(const function &f)
{
    domain domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].first);

    return domain;
}

codomain get_codomain(const function &f)
{
    codomain codomain;
    for (unsigned int i = 0; i < f.size(); i++)
        codomain.push_back(f[i].second);

    return codomain;
}

function get_function(const domain &d, const codomain &c)
{
    if (d.size() != c.size())
        throw std::logic_error("domain and codomain have a different number of elements");

    function f;
    for (unsigned int i = 0; i < d.size(); i++)
        f.push_back(std::make_pair(d[i], c[i]));

    return f;
}