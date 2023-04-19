#pragma once

#include "../statistics.h"
#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include <iostream>
#include <map>

std::map<std::string, function> fft(const std::map<std::string, function> &fs)
{
    std::map<std::string, function> spectra;
    for (const std::pair<std::string, function> f : fs)
    {
        std::string name = f.first;
        kiss_fft_cpx in[f.second.size()];
        kiss_fft_cpx out[f.second.size()];
        std::vector<default_type> x = get_domain(f.second);
        std::vector<default_type> y = get_codomain(f.second);
        default_type sampling_time = x[1] - x[0];
        for (unsigned int i = 0; i < f.second.size(); i++)
        {
            in[i] = {(kiss_fft_scalar)y[i], 0};
            if (sampling_time != 0 && i > 0 && std::fabs(sampling_time - (x[i] - x[i - 1]) > 100 * std::numeric_limits<default_type>::epsilon()))
                sampling_time = 0;
        }

        kiss_fft_cfg cfg;
        if ((cfg = kiss_fft_alloc(f.second.size(), 0, NULL, NULL)) != NULL)
        {
            kiss_fft(cfg, in, out);
            free(cfg);
            const bool full = false;
            if (sampling_time == 0)
                std::cout << "Warning! sampling time is 0: time is not linear or intervals are not regular" << std::endl;

            function spectrum;
            std::ofstream output_file("output/fft_" + name);
            output_file << "freq,power" << std::endl;
            for (unsigned int j = 0; j < (full ? f.second.size() : (f.second.size() / 2 + 1)); j++)
            {
                default_type freq = (sampling_time == 0 ? 1 : sampling_time) * (default_type)(f.second.size()) / (default_type)j;
                default_type power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                output_file << freq << "," << power << std::endl;
                spectrum.push_back(std::pair(freq, power));
            }

            spectra[name] = spectrum;
            output_file.close();
        }
        else
            throw std::runtime_error("error allocating fft " + name);
    }

    return spectra;
}

std::map<std::string, function> get_peaks(const std::map<std::string, function> &fs, const unsigned int &number_of_peaks)
{
    std::map<std::string, function> peaks;

    for (const std::pair<std::string, function> f : fs)
    {
        std::string name = f.first;

        // order descending (greather first)
        function f_cp(f.second);
        std::sort(f_cp.begin(), f_cp.end(), [=](pair &a, pair &b)
                  { return a.second > b.second; });

        function peak;
        std::ofstream output_file("output/fft_peaks_" + name);
        output_file << "index,freq,power" << std::endl;
        for (unsigned int i = 0; i < number_of_peaks; i++)
        {
            peak.push_back(f_cp[i]);
            output_file << i << "," << f_cp[i].first << "," << f_cp[i].second << std::endl;
        }

        peaks[name] = peak;
        output_file.close();
    }

    return peaks;
}