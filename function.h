#pragma once

#include <vector>

#define DECIMAL

#ifdef DECIMAL
#define ddt double // Domain Default Type
#define cdt double // Codomain Default Type
#else
#define ddt unsigned long int
#define cdt unsigned long int
#endif

#define polyfit_max_degree 10
#define fft_peaks_number 5
#define DOM_CODOM_DIM 2

using pair = std::pair<ddt, cdt>;
using function = std::vector<pair>;

std::vector<ddt> get_domain(const function &f)
{
    std::vector<ddt> domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].first);

    return domain;
}

std::vector<cdt> get_codomain(const function &f)
{
    std::vector<cdt> domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].second);

    return domain;
}