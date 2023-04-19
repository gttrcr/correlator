/*

#pragma once

#include <vector>

template <unsigned int domain_dim, unsigned int codomain_dim>
std::vector<function<1, domain_dim>> rotate_fs(const std::vector<std::tuple<std::string, function<domain_dim, codomain_dim>>> &fs)
{
    std::vector<function<1, domain_dim>> rotated(std::get(fs[0]).size());
    for (unsigned int i = 0; i < rotated.size(); i++)
    {
        for (unsigned int j = 0; j < fs.size(); j++)
            rotated[i].set(domain(j), std::get(fs[j]).get_domain(i));
    }

    return rotated;
}

template <unsigned int domain_dim, unsigned int codomain_dim>
void peaks_migration(const std::vector<std::tuple<std::string, function<domain_dim, codomain_dim>>> &fs)
{
    std::vector<function<1, domain_dim>> rfs = rotate_fs(fs); // rotate the input
    for (unsigned int i = 0; i < rfs.size(); i++)
        polyfit::pf(rfs[i], rfs[0].size(), std::to_string(i + 1) + "_peak_migration");
}
*/