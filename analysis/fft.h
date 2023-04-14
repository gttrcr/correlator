#pragma once

#include "../statistics.h"
#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

// TODO improve multifft transform on domain_size
template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<1, 1>>> fft(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs)
{
    std::vector<std::tuple<std::string, function<1, 1>>> spectra;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        std::string name = std::get<0>(fs[i]);
        function<domain_size, codomain_size> f = std::get<1>(fs[i]);
        kiss_fft_cpx in[f.size()];
        kiss_fft_cpx out[f.size()];
        long_t_space sampling_time = (f.get_domain(1) - f.get_domain(0)).val();
        for (unsigned int j = 0; j < f.size(); j++)
        {
            in[j] = {(kiss_fft_scalar)f.get_codomain(j).val(), 0};
            if (sampling_time != 0 && j > 0 && std::fabs(sampling_time - (f.get_domain(j) - f.get_domain(j - 1)).val()) > 100 * std::numeric_limits<t_space>::epsilon())
                sampling_time = 0;
        }

        kiss_fft_cfg cfg;
        if ((cfg = kiss_fft_alloc(f.size(), 0, NULL, NULL)) != NULL)
        {
            kiss_fft(cfg, in, out);
            free(cfg);
            const bool full = false;
            if (sampling_time == 0)
                std::cout << "Warning! sampling time is 0: time is not linear or intervals are not regular" << std::endl;
            function<1, 1> spectrum;
            for (unsigned int j = 0; j < (full ? f.size() : (f.size() / 2 + 1)); j++)
            {
                long_t_space freq = (sampling_time == 0 ? 1 : sampling_time) * (long_t_space)(f.size()) / (long_t_space)j;
                long_t_space power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                std::cout << freq << " " << power << std::endl;
                spectrum.set(domain<1>(freq), codomain<1>(power));
            }

            spectra.push_back(std::make_tuple(name, spectrum));
        }
        else
            throw std::runtime_error("error allocating fft " + name);
    }

    return spectra;
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<domain_size, 1>>> get_norm_peaks(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs, const unsigned int &number_of_peaks)
{
    std::vector<std::tuple<std::string, function<domain_size, 1>>> norm_peaks;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        std::string name = std::get<0>(fs[i]);
        function<domain_size, codomain_size> f = std::get<1>(fs[i]);
        norm_peaks.push_back(std::make_tuple(name, f.maximas(number_of_peaks)));
    }

    return norm_peaks;
}