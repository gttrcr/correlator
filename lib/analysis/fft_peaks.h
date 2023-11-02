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
            SOURCE source;
            corr_function peaks;
        };

        corr_function _spectrum;
        arguments _args;
        data _data;

    public:
        fft_peaks(corr_function spectrum, const arguments &args)
        {
            _spectrum = spectrum;
            _args = args;
        }

        void compute(const SOURCE &source)
        {
            // order descending (greather first)
            DOMAIN spectrum_domain = _spectrum.get_domain();
            CODOMAIN spectrum_codomain = _spectrum.get_codomain();
            std::vector<PAIR> f_cp;
            for (unsigned int i = 0; i < spectrum_domain.size(); i++)
                f_cp.push_back(std::make_pair(spectrum_domain[i], spectrum_codomain[i]));
            std::sort(f_cp.begin(), f_cp.end(), [=](PAIR &a, PAIR &b)
                      { return a.second > b.second; });

            unsigned int n_peaks = std::min(_args.number_of_fft_peaks_to_compute, (unsigned int)f_cp.size());
            f_cp = std::vector<PAIR>(f_cp.begin(), f_cp.begin() + n_peaks);
            _data = {source, corr_function(f_cp)};
        }

        // save all computed peaks and clear all _data
        void save(const std::string &output_folder, const std::string &output_file) const
        {
            std::filesystem::create_directory(_args.output + "/" + output_folder);
            std::ofstream of(_args.output + "/" + output_folder + "/" + _data.source.first + "_" + output_file);
            analysis::result::get()->set_analysis(output_folder, _data.source.first + "_" + output_file);
            of << "index,freq,power" << std::endl;
            DOMAIN d = _data.peaks.get_domain();     // frequency
            CODOMAIN c = _data.peaks.get_codomain(); // power
            for (unsigned int j = 0; j < d.size(); j++)
                of << j << "," << d[j] << "," << c[j] << std::endl;
            of.close();
        }

        corr_function get_peaks() const
        {
            return _data.peaks;
        }
    };
}