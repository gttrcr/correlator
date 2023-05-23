#pragma once

#include "fft.h"
#include "fft_peaks.h"
#include "polyfit.h"
#include "peaks_migration.h"
#include "entropy.h"

#include <filesystem>

namespace analysis
{
    // compute best polynomial fit
    void polyfit_method(const std::map<std::string, function> &fs, const arguments& args)
    {
        std::cout << "\tpolyfit..." << std::endl;
        polyfit pf(args);

        // compute correlation of every function
        std::cout << "\t\tsingle function..." << std::endl;
        for (const std::pair<std::string, function> &f : fs)
            pf.compute(f.second, POLYFIT_MAX_DEGREE, "polyfit_" + std::filesystem::path(f.first).stem().string());

        // compute cross correlation between every pair
        std::cout << "\t\tcross correlation..." << std::endl;
        for (const std::pair<std::string, function> &f : fs)
            for (const std::pair<std::string, function> &g : fs)
            {
                if (f.first == g.first)
                    continue;

                domain d = get_codomain(f.second);
                codomain c = get_codomain(g.second);
                function cross_f = get_function(d, c);
                pf.compute(cross_f, POLYFIT_MAX_DEGREE, "polyfit_" + std::filesystem::path(f.first).stem().string() + "_VS_" + std::filesystem::path(g.first).stem().string());
            }
    }

    // compute fft of every dataset and compute peaks of every fft
    std::map<std::string, function> fft_and_fft_peaks(const std::map<std::string, function> &fs, const arguments& args)
    {
        // map of peaks of every function in fs
        std::map<std::string, function> peaks;

        std::cout << "\tfft..." << std::endl;
        fft fft(args);
        for (const std::pair<std::string, function> &f : fs)
        {
            if (!fft.compute(f.second, f.first))
                std::cout << "Error on computing fft " << f.first << std::endl;
            function spectrum = fft.get_spectrum();
            std::cout << "\t\tpeaks..." << std::endl;
            peaks[f.first] = fft_peaks(spectrum, args).compute(FFT_PEAKS_NUMBER, f.first);
        }

        return peaks;
    }

    void peaks_migration(const std::map<std::string, function> &peaks, const arguments& args)
    {
        // std::cout << "peaks migration..." << std::endl;
        // std::map<std::string, function> rotated_peaks = rotate(peaks);
        // for (const std::pair<std::string, function> &f : rotated_peaks)
        //     pf.compute(f.second, f.second.size(), "peak_migr" + std::filesystem::path(f.first).stem().string());
    }

    void all_methods(const std::map<std::string, function> &fs, const arguments& args)
    {
        std::filesystem::create_directory(args.output);

        polyfit_method(fs, args);
        std::map<std::string, function> peaks = fft_and_fft_peaks(fs, args);
        peaks_migration(peaks, args);

#ifdef INTEGERS
        seeker::compute();
#endif
    }
}