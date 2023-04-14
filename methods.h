#pragma once

#include "analysis/polyfit.h"
#include "analysis/fft.h"
#include "analysis/peaks_migration.h"

#include <fstream>
#include <filesystem>

template <unsigned int domain_size, unsigned int codomain_size>
void methods(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs)
{
    std::filesystem::create_directory("output");

    // compute best polynomial fit
    std::cout << "polyfit..." << std::endl;
    polyfit::pf(fs, polyfit_max_degree, "polyfit");

    // compute fft of vector of fs and return their peaks
    std::cout << "fft" << std::endl;
    std::vector<std::tuple<std::string, function<default_type, 1, 1>>> spectra = fft(fs);

    // get peaks
    std::cout << "peaks..." << std::endl;
    std::vector<std::tuple<std::string, function<default_type, 1, 1>>> peaks = get_norm_peaks(spectra, fft_peaks_number);

    std::cout << "peaks polyfit..." << std::endl;
    peaks_migration(peaks);

    // std::cout << "peaks fft..." << std::endl;
    // peaks_fft();
}