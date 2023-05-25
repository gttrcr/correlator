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
            function peaks;
        };

        function _spectrum;
        arguments _args;
        std::vector<data> _data;

    public:
        fft_peaks(function spectrum, const arguments &args)
        {
            _spectrum = spectrum;
            _args = args;
        }

        void compute(const std::string &name)
        {
            // order descending (greather first)
            function f_cp(_spectrum);
            std::sort(f_cp.begin(), f_cp.end(), [=](pair &a, pair &b)
                      { return a.second > b.second; });

            unsigned int n_peaks = std::min(_args.number_of_peaks_to_find, (unsigned int)f_cp.size());
            _data.push_back({name, function(f_cp.begin(), f_cp.begin() + n_peaks)});
        }

        // save all computed peaks and clear all _data
        void save(const std::string &output_folder)
        {
            std::filesystem::create_directory(_args.output + "/" + output_folder);
            for (unsigned int i = 0; i < _data.size(); i++)
            {
                std::ofstream of(_args.output + "/" + output_folder + "/" + _data[i].name + ".csv");
                of << "index,freq,power" << std::endl;
                domain d = get_domain(_data[i].peaks);     // frequency
                codomain c = get_codomain(_data[i].peaks); // power
                for (unsigned int j = 0; j < d.size(); j++)
                    of << j << "," << d[j] << "," << c[j] << std::endl;
                of.close();
            }

            _data.clear();
        }
    };
}