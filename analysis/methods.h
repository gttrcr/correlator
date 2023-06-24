#pragma once

#include "fft.h"
#include "fft_peaks.h"
#include "polyfit.h"
#include "entropy.h"
#include "../utils.h"

typedef std::vector<std::pair<std::string, FUNCTION>> FUNCTIONS;

#include <filesystem>

namespace analysis
{
    // compute best polynomial fit
    void polyfit_method(const FUNCTIONS &fs, const arguments &args)
    {
        std::cout << "\tpolyfit..." << std::endl;
        polyfit pf(args);

        // compute correlation of every function
        std::cout << "\t\tsingle function..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            pf.compute(fs.at(i).second, args.polyfit_max_degree, fs.at(i).first);
        pf.save("polyfit", "single");

        // compute cross correlation between every pair
        std::cout << "\t\tcross correlation..." << std::endl;
        for (unsigned int i = 0; i < fs.size(); i++)
            for (unsigned int j = i + 1; j < fs.size(); j++)
                pf.compute(get_function(get_codomain(fs.at(i).second), get_codomain(fs.at(j).second)),
                           args.polyfit_max_degree,
                           fs.at(i).first + "_+_" + fs.at(j).first);

        pf.save("polyfit", "cross");
    }

    // compute fft of every dataset and peaks of every fft
    std::map<std::string, FUNCTION> fft_and_fft_peaks(const FUNCTIONS &fs, const arguments &args)
    {
        // map of peaks of every function in fs
        std::map<std::string, FUNCTION> peaks;

        std::cout << "\tfft..." << std::endl;
        fft fft(args);
        for (unsigned int i = 0; i < fs.size(); i++)
        {
            fft.compute(fs.at(i).second, fs.at(i).first);
            FUNCTION spectrum = fft.get_last_spectrum();
            fft.save("fft");
            std::cout << "\t\tpeaks..." << std::endl;
            fft_peaks fft_peaks(spectrum, args);
            fft_peaks.compute(fs.at(i).first);
            fft_peaks.save("peaks");
        }

        return peaks;
    }

    // compute the polynomial fit of migration of peaks
    void peaks_migration(const std::map<std::string, FUNCTION> &peaks, const arguments &args)
    {
        // std::cout << "\tpeaks migration..." << std::endl;
        // polyfit pf(args);
        // std::map<std::string, function> rotated_peaks = utils::rotate(peaks);
        // for (const std::pair<std::string, function> &f : rotated_peaks)
        //     pf.compute(f.second, f.second.size(), "peak_migr" + f.first);
    }

    // compute the real time fft and peaks of every fft
    void rt_fft_and_fft_peaks(const FUNCTIONS &fs, const arguments &args)
    {
        // std::cout << "\trt fft..." << std::endl;
        // ddt interval_size = 0.01;
        // for (const std::pair<std::string, function> &f : fs)
        // {
        //     ddt sample_size;
        //     if (!get_sampling(f.second, sample_size))
        //         continue;

        //     fft fft(args);
        //     unsigned int number_of_points = 400; // 2 * M_PI * 3 * sample_size;
        //     for (unsigned int i = 0; i < f.second.size() / number_of_points; i++)
        //     {
        //         function interval_function = get_interval(f.second, i * number_of_points, number_of_points);
        //         fft.compute(interval_function, f.first + std::to_string(i));
        //         // function peaks = fft_peaks(fft.get_spectrum(), args).compute(FFT_PEAKS_NUMBER);
        //         // std::cout << peaks[0].first << std::endl;
        //     }
        // }
    }

    void all_methods(const FUNCTIONS &fs, const arguments &args)
    {
        if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output))
            throw correlator_exception(error::cannot_create_output_directory);

        polyfit_method(fs, args);                                            // OK: tested!
        std::map<std::string, FUNCTION> peaks = fft_and_fft_peaks(fs, args); // OK: tested!

        peaks_migration(peaks, args);   // must be tested
        rt_fft_and_fft_peaks(fs, args); // must be tested
    }
}