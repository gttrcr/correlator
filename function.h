#pragma once

#include <vector>

#define default_type double
#define polyfit_max_degree 10
#define fft_peaks_number 5
#define DOM_CODOM_DIM 2

using pair = std::pair<default_type, default_type>;
using function = std::vector<pair>;

std::vector<default_type> get_domain(const function &f)
{
    std::vector<default_type> domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].first);

    return domain;
}

std::vector<default_type> get_codomain(const function &f)
{
    std::vector<default_type> domain;
    for (unsigned int i = 0; i < f.size(); i++)
        domain.push_back(f[i].second);

    return domain;
}