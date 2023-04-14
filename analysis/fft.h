#pragma once

#include "../statistics.h"
#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

// TODO improve multifft on domain_size
template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<default_type, 1, 1>>> fft(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs)
{
    std::vector<std::tuple<std::string, function<default_type, 1, 1>>> spectra(fs.size());
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        std::string name = std::get<0>(fs[i]);
        std::get<0>(spectra[i]) = name;
        function<default_type, domain_size, codomain_size> f = std::get<1>(fs[i]);
        kiss_fft_cpx in[f.size()];
        kiss_fft_cpx out[f.size()];
        default_type sampling_time = (f.get_domain(1) - f.get_domain(0)).val();
        for (unsigned int j = 0; j < f.size(); j++)
        {
            in[j] = {(kiss_fft_scalar)f.get_codomain(j).val(), 0};
            if (sampling_time != 0 && j > 0 && std::fabs(sampling_time - (f.get_domain(j) - f.get_domain(j - 1)).val()) > 100 * std::numeric_limits<default_type>::epsilon())
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

            std::ofstream output_file("output/fft_" + name);
            output_file << "freq,power" << std::endl;
            for (unsigned int j = 0; j < (full ? f.size() : (f.size() / 2 + 1)); j++)
            {
                default_type freq = (sampling_time == 0 ? 1 : sampling_time) * (default_type)(f.size()) / (default_type)j;
                default_type power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                output_file << freq << "," << power << std::endl;
                std::get<1>(spectra[i]).set(domain<default_type, 1>(freq), codomain<default_type, 1>(power));
            }

            output_file.close();
        }
        else
            throw std::runtime_error("error allocating fft " + name);
    }

    return spectra;
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::tuple<std::string, function<default_type, domain_size, 1>>> get_norm_peaks(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs, const unsigned int &number_of_peaks)
{
    std::vector<std::tuple<std::string, function<default_type, domain_size, 1>>> norm_peaks;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        std::string name = std::get<0>(fs[i]);
        function<default_type, domain_size, codomain_size> f = std::get<1>(fs[i]);
        function<default_type, domain_size, codomain_size> max = f.maximas(number_of_peaks);
        norm_peaks.push_back(std::make_tuple(name, max));

        std::ofstream output_file("output/fft_peaks_" + name);
        output_file << "freq,power" << std::endl;
        for (unsigned int j = 0; j < max.size(); j++)
            output_file << max.get_domain(j).val() << "," << max.get_codomain(j).val() << std::endl;

        output_file.close();
    }

    return norm_peaks;
}