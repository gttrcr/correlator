#pragma once

#include "../function.h"

#include <iostream>
#include <fstream>
#include <algorithm>

namespace analysis
{
    class fft_peaks
    {
    private:
        struct data
        {
        public:
            std::string name;
            corr_function peaks;
        };

        corr_function _spectrum;
        arguments _args;
        std::vector<data> _data;

    public:
        fft_peaks(corr_function spectrum, const arguments &args)
        {
            _spectrum = spectrum;
            _args = args;
        }

        void compute(const std::string &name)
        {
            // order descending (greather first)
            DOMAIN spectrum_domain = _spectrum.get_codomain();
            CODOMAIN spectrum_codomain = _spectrum.get_codomain();
            std::vector<PAIR> f_cp;
            for (unsigned int i = 0; i < spectrum_domain.size(); i++)
                f_cp.push_back(std::make_pair(spectrum_domain[i], spectrum_codomain[i]));
            std::sort(f_cp.begin(), f_cp.end(), [=](PAIR &a, PAIR &b)
                      { return a.second > b.second; });

            unsigned int n_peaks = std::min(_args.number_of_fft_peaks_to_compute, (unsigned int)f_cp.size());
            f_cp = std::vector<PAIR>(f_cp.begin(), f_cp.begin() + n_peaks);
            _data.push_back({name, corr_function(f_cp)});
        }

        // save all computed peaks and clear all _data
        void save(const std::string &output_folder)
        {
            std::filesystem::create_directory(_args.output + "/" + output_folder);
            for (unsigned int i = 0; i < _data.size(); i++)
            {
                std::ofstream of(_args.output + "/" + output_folder + "/" + _data[i].name + ".csv");
                of << "index,freq,power" << std::endl;
                DOMAIN d = _data[i].peaks.get_domain();     // frequency
                CODOMAIN c = _data[i].peaks.get_codomain(); // power
                for (unsigned int j = 0; j < d.size(); j++)
                    of << j << "," << d[j] << "," << c[j] << std::endl;
                of.close();
            }

            _data.clear();
        }
    };
}