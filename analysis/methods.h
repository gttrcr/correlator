#pragma once

#include "fft.h"
#include "polyfit.h"
#include "peaks_migration.h"
#include "entropy.h"

#include <filesystem>

namespace analysis
{
    void methods(const std::map<std::string, function> &fs)
    {
        entropy en;
        en.step(4);
        en.step(4);
        en.step(4);
        en.step(5);
        
        std::filesystem::create_directory("output");

        // compute best polynomial fit
        std::cout << "polyfit..." << std::endl;
        polyfit pf;
        for (const std::pair<std::string, function> f : fs)
            pf.compute(f.second, polyfit_max_degree, "polyfit_" + std::filesystem::path(f.first).stem().string());
        if (fs.size() > 1)
            pf.compute(fs, polyfit_max_degree, "polyfit");

        // compute fft of vector of fs and return their peaks
        std::cout << "fft..." << std::endl;
        fft fft;
        if (!fft.compute(fs))
            std::cout << "Error on computing fft" << std::endl;

        // get peaks
        std::cout << "peaks..." << std::endl;
        std::map<std::string, function> peaks = fft.get_peaks(fft_peaks_number);

        // peaks migration
        std::cout << "peaks polyfit..." << std::endl;
        std::map<std::string, function> rotated_peaks = rotate(peaks);
        for (const std::pair<std::string, function> f : rotated_peaks)
            pf.compute(f.second, f.second.size(), "peak_migr" + std::filesystem::path(f.first).stem().string());

#ifdef INTEGERS
        seeker::compute();
#endif
    }
}