#pragma once

#include "polyfit.h"
#include "fft.h"
#include "fft_peaks.h"
#include "result.h"
#include "../utils.h"
#include "../error.h"

// #include <filesystem>

namespace analysis
{
    // compute best polynomial fit
    void polyfit_work(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tPolyfit..." << std::endl;
        polyfit pf(args);

        // compute correlation of every function
        std::cout << "\t\tSingle function..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            pf.compute(fs.at(i).second, args.polyfit_max_degree, fs.at(i).first);
        pf.save("Polyfit", "single.csv");
        analysis::result::get()->set_analysis("Polyfit", "single.csv");

        // compute cross correlation between every pair
        std::cout << "\t\tCross correlation..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            for (unsigned int j = i + 1; j < fs.size(); j++)
                pf.compute(corr_function(fs.at(i).second.get_codomain(), fs.at(j).second.get_codomain()),
                           args.polyfit_max_degree,
                           fs.at(i).first + "_+_" + fs.at(j).first);

        pf.save("Polyfit", "cross.csv");
        analysis::result::get()->set_analysis("Polyfit", "cross.csv");
    }

    // compute fft of every dataset and peaks of every fft
    FUNCTIONS fft_work(const FUNCTIONS &fs, const arguments &args)
    {
        // map of peaks of every function in fs
        FUNCTIONS peaks;

        std::cout << "\tFFT..." << std::endl;
        fft fft(args);
        for (unsigned int i = 0; i < fs.size(); i++)
        {
            std::cout << "\t\tSpectrum..." << std::endl;
            fft.compute(fs.at(i).second, fs.at(i).first);
            fft.save("FFT", "fft.csv");
            std::cout << "\t\tPeaks..." << std::endl;
            fft_peaks fft_peaks(fft.get_spectrum(), args);
            fft_peaks.compute(fs.at(i).first);
            fft_peaks.save("FFT", "peaks.csv");
            peaks.push_back({fs.at(i).first, fft_peaks.get_peaks()});
        }

        return peaks;
    }

    // // compute the polynomial fit of migration of peaks
    // void peaks_migration(const FUNCTIONS &peaks, const arguments &args)
    // {
    //     // std::cout << "\tPeaks migration..." << std::endl;
    //     // polyfit pf(args);
    //     // std::map<std::string, function> rotated_peaks = utils::rotate(peaks);
    //     // for (const std::pair<std::string, function> &f : rotated_peaks)
    //     //     pf.compute(f.second, f.second.size(), "peak_migr" + f.first);
    // }

    void work(const FUNCTIONS &fs, const arguments &args)
    {
        if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output))
            throw correlator_exception(error::cannot_create_output_directory);

        polyfit_work(fs, args);               // tested
        FUNCTIONS peaks = fft_work(fs, args); // tested
        // peaks_migration(peaks, args); // must be tested
    }
}