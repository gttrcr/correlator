#pragma once

#include "polyfit.h"
#include "fft.h"
#include "fft_peaks.h"
#include "pattern_matching.h"
#include "result.h"

#include "../utils.h"
#include "../error.h"

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
            pf.compute(fs[i].second, args.polyfit_max_degree, fs[i].first);
        pf.save("Polyfit", "single.csv");
        analysis::result::get()->set_analysis("Polyfit", "single.csv");

        // compute cross correlation of every pair
        std::cout << "\t\tCross correlation..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            for (unsigned int j = i + 1; j < fs.size(); j++)
            {
                corr_function f(fs[i].second.get_codomain(), fs[j].second.get_codomain());
                pf.compute(f, args.polyfit_max_degree, fs[i].first, fs[j].first);
            }
        pf.save("Polyfit", "cross.csv");
        analysis::result::get()->set_analysis("Polyfit", "cross.csv");
    }

    // compute fft of every dataset and peaks of every fft
    FUNCTIONS fft_work(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tFFT..." << std::endl;

        // map of peaks of every function in fs
        FUNCTIONS peaks;
        fft fft(args);
        for (unsigned int i = 0; i < fs.size(); i++)
        {
            std::cout << "\t\tSpectrum..." << std::endl;
            fft.compute(fs[i].second, fs[i].first);
            fft.save("FFT", "fft.csv");
            std::cout << "\t\tPeaks..." << std::endl;
            fft_peaks fft_peaks(fft.get_spectrum(), args);
            fft_peaks.compute(fs[i].first);
            fft_peaks.save("FFT", "peaks.csv");
            peaks.push_back({fs[i].first, fft_peaks.get_peaks()});
        }

        return peaks;
    }

    // scan every datafile and return common pattern
    void pattern_matching_work(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tPattern matching..." << std::endl;

        pattern_matching pm(args);
        for (unsigned int i = 0; i < fs.size(); i++)
            pm.compute(fs[i].second, fs[i].first);
    }

    void work(const FUNCTIONS &fs, const arguments &args)
    {
        if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output))
            throw correlator_exception(error::cannot_create_output_directory);

        polyfit_work(fs, args);               // tested
        FUNCTIONS peaks = fft_work(fs, args); // tested
        pattern_matching_work(fs, args);      // in progress...
    }
}