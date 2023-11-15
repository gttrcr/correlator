#pragma once

#include "polyfit.h"
#include "fft.h"
#include "fft_peaks.h"
#include "pattern_matching.h"
#include "result.h"

#include "../utils.h"

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
        analysis::metadata::get()->set_analysis("Polyfit", "single.csv");

        // compute multithread cross correlation of every pair
        std::cout << "\t\tCross correlation..." << std::endl;
        std::vector<std::tuple<corr_function, unsigned int, SOURCE, SOURCE>> parallelizable;
        for (unsigned int i = 0; i < fs.size(); i++)
            for (unsigned int j = i + 1; j < fs.size(); j++)
                parallelizable.push_back(std::make_tuple(corr_function(fs[i].second.get_codomain(), fs[j].second.get_codomain()), args.polyfit_max_degree, fs[i].first, fs[j].first));
#ifdef THREAD_SUPPORT
        std::for_each(std::execution::par_unseq, parallelizable.begin(), parallelizable.end(), [&](std::tuple<corr_function, unsigned int, SOURCE, SOURCE> p)
                      {
#else
        for (std::tuple<corr_function, unsigned int, SOURCE, SOURCE> p : parallelizable)
#endif
                          pf.compute(std::get<0>(p), std::get<1>(p), std::get<2>(p), std::get<3>(p));
#ifdef THREAD_SUPPORT
                      });
#endif

        pf.save("Polyfit", "cross.csv");
        analysis::metadata::get()->set_analysis("Polyfit", "cross.csv");
    }

    // compute fft of every dataset and peaks of every fft
    void fft_work(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tFFT..." << std::endl;

        // map of peaks of every function in fs. TODO multithread
        fft fft(args);
        for (unsigned int i = 0; i < fs.size(); i++)
        {
            std::cout << "\t\tSpectrum..." << std::endl;
            fft.compute(fs[i].second, fs[i].first);
            fft.save("FFT", "fft_" + fs[i].first.first + "_" + fs[i].first.second + ".csv");

            std::cout << "\t\tPeaks..." << std::endl;
            fft_peaks fft_peaks(fft.get_spectrum(), args);
            fft_peaks.compute(fs[i].first);
            fft_peaks.save("FFT", "peaks" + fs[i].first.first + "_" + fs[i].first.second + ".csv");
        }
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
        std::cout << "Working on " << fs.size() << " files..." << std::endl;

        if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output))
            std::cerr << "Cannot create output directory " << args.output << std::endl;

        if (args.compute_polyfit)
            polyfit_work(fs, args); // OK

        if (args.compute_fft)
            fft_work(fs, args); // OK

        // pattern_matching_work(fs, args); // in progress...
    }
}