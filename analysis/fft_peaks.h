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
        function _spectrum;
        arguments _args;

    public:
        fft_peaks(function spectrum, const arguments &args)
        {
            _spectrum = spectrum;
            _args = args;
        }

        function compute(const unsigned int &number_of_peaks, const std::string &name = "")
        {
            // order descending (greather first)
            function f_cp(_spectrum);
            std::sort(f_cp.begin(), f_cp.end(), [=](pair &a, pair &b)
                      { return a.second > b.second; });

            function peak;
            for (unsigned int i = 0; i < number_of_peaks; i++)
                peak.push_back(f_cp[i]);

            if (!name.empty())
            {
                std::ofstream output_file(_args.output + "/fft_peaks_" + name);
                output_file << "index,freq,power" << std::endl;
                for (unsigned int i = 0; i < number_of_peaks; i++)
                    output_file << i << "," << f_cp[i].first << "," << f_cp[i].second << std::endl;
                output_file.close();
            }

            return peak;
        }
    };
}