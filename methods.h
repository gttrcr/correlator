#pragma once

#include "analysis/polyfit.h"
#include "analysis/fft.h"
#include "analysis/peaks_migration.h"

#include <fstream>
#include <filesystem>

template <unsigned int domain_size, unsigned int codomain_size>
void methods(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs)
{
    std::filesystem::create_directory("output");

    // compute best polynomial fit
    polyfit(fs, 15);

    // compute fft of vector of fs and return their peaks
    std::vector<std::tuple<std::string, function<1, 1>>> spectra = fft(fs);
    std::vector<std::tuple<std::string, function<1, 1>>> peaks = get_norm_peaks(spectra, 5);
    peaks_migration(peaks);

    // ret_peaks.push_back(std::make_tuple(name, peaks(power_spectrum, 5)));
    //  for (unsigned int i = 0; i < peaks.size(); i++)
    //{
    //      // std::ofstream output_file("output/fft_peak_" + std::get<0>(fs[0]) + ".csv");
    //      // output_file << "frequency,power" << std::endl;
    //      // for (unsigned int j = 0; j < peaks[i].size(); j++)
    //      //     output_file << peaks[i][j] << ",";
    //      // output_file << std::endl;
    //      // output_file.close();
    //  }
}