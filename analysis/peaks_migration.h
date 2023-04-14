#pragma once

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> rotate_fs(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs)
{
    std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> rotated(std::get<1>(fs[0]).size());
    for (unsigned int i = 0; i < rotated.size(); i++)
    {
        std::get<0>(rotated[i]) = std::get<0>(fs[0]);
        for (unsigned int j = 0; j < fs.size(); i++)
            std::get<1>(rotated[i]).set(domain<1>(j), std::get<1>(fs[j]).get_codomain(i));
    }

    return rotated;
}

template <unsigned int domain_size, unsigned int codomain_size>
void peaks_migration(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs)
{
    std::vector<std::tuple<std::string, function<1, 1>>> rfs = rotate_fs(fs);
}