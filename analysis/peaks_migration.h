#pragma once

#include <vector>

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<function<default_type, 1, domain_size>> rotate_fs(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs)
{
    std::vector<function<default_type, 1, domain_size>> rotated(std::get<1>(fs[0]).size());
    for (unsigned int i = 0; i < rotated.size(); i++)
    {
        for (unsigned int j = 0; j < fs.size(); j++)
            rotated[i].set(domain<default_type, 1>(j), std::get<1>(fs[j]).get_domain(i));
    }

    return rotated;
}

template <unsigned int domain_size, unsigned int codomain_size>
void peaks_migration(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs)
{
    std::vector<function<default_type, 1, domain_size>> rfs = rotate_fs(fs); // rotate the input
    for (unsigned int i = 0; i < rfs.size(); i++)
        polyfit::pf(rfs[i], rfs[0].size(), std::to_string(i + 1) + "_peak_migration");
}