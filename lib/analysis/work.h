#pragma once

#include "polyfit.h"
#include "fft.h"
#include "fft_peaks.h"
#include "result.h"
#include "../utils.h"
#include "../error.h"

#include <filesystem>

namespace analysis
{
    // compute best polynomial fit
    void polyfit_work(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tpolyfit..." << std::endl;
        polyfit pf(args);

        // compute correlation of every function
        std::cout << "\t\tsingle function..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            pf.compute(fs.at(i).second, args.polyfit_max_degree, fs.at(i).first);
        pf.save("polyfit", "single");
        analysis::result::get()->set_analysis("polyfit", "single");

        // compute cross correlation between every pair
        std::cout << "\t\tcross correlation..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            for (unsigned int j = i + 1; j < fs.size(); j++)
                pf.compute(corr_function(fs.at(i).second.get_codomain(), fs.at(j).second.get_codomain()),
                           args.polyfit_max_degree,
                           fs.at(i).first + "_+_" + fs.at(j).first);

        pf.save("polyfit", "cross");
        analysis::result::get()->set_analysis("polyfit", "cross");
    }

    // // compute fft of every dataset and peaks of every fft
    // std::map<std::string, corr_function> fft_work(const FUNCTIONS &fs, const arguments &args)
    // {
    //     // map of peaks of every function in fs
    //     std::map<std::string, corr_function> peaks;

    //     std::cout << "\tfft..." << std::endl;
    //     fft fft(args);
    //     for (unsigned int i = 0; i < fs.size(); i++)
    //     {
    //         fft.compute(fs.at(i).second, fs.at(i).first);
    //         corr_function spectrum = fft.get_last_spectrum();
    //         fft.save("fft");
    //         std::cout << "\t\tpeaks..." << std::endl;
    //         fft_peaks fft_peaks(spectrum, args);
    //         fft_peaks.compute(fs.at(i).first);
    //         fft_peaks.save("peaks");
    //     }

    //     return peaks;
    // }

    // // compute the polynomial fit of migration of peaks
    // void peaks_migration(const std::map<std::string, corr_function> &peaks, const arguments &args)
    // {
    //     // std::cout << "\tpeaks migration..." << std::endl;
    //     // polyfit pf(args);
    //     // std::map<std::string, function> rotated_peaks = utils::rotate(peaks);
    //     // for (const std::pair<std::string, function> &f : rotated_peaks)
    //     //     pf.compute(f.second, f.second.size(), "peak_migr" + f.first);
    // }

    void work(const FUNCTIONS &fs, const arguments &args)
    {
        if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output))
            throw correlator_exception(error::cannot_create_output_directory);

        polyfit_work(fs, args); // OK: tested!
        // std::map<std::string, corr_function> peaks = fft_work(fs, args);
        // peaks_migration(peaks, args); // must be tested
    }
}