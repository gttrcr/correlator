#pragma once

#include "function.h"
#include "analysis/polyfit.h"
#include "analysis/fft.h"
#include "analysis/peaks_migration.h"

#include <fstream>
#include <filesystem>
#include <map>
#include <iostream>

void methods(const std::map<std::string, function> &fs)
{
    std::filesystem::create_directory("output");

    // compute best polynomial fit
    std::cout << "polyfit..." << std::endl;
    for (const std::pair<std::string, function> f : fs)
        polyfit::pf(f.second, polyfit_max_degree, "polyfit_" + std::filesystem::path(f.first).stem().string());
    if (fs.size() > 1)
        polyfit::pf(fs, polyfit_max_degree, "polyfit");

    // compute fft of vector of fs and return their peaks
    std::cout << "fft" << std::endl;
    std::map<std::string, function> spectra = fft(fs);

    // get peaks
    std::cout << "peaks..." << std::endl;
    std::map<std::string, function> peaks = get_peaks(spectra, fft_peaks_number);
    //
    // std::cout << "peaks polyfit..." << std::endl;
    // peaks_migration(peaks);

    // std::cout << "peaks fft..." << std::endl;
    // peaks_fft();
}