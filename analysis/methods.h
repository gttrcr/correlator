#pragma once

#include "fft.h"
#include "fft_peaks.h"
#include "polyfit.h"
#include "entropy.h"
#include "../utils.h"

#include <filesystem>

namespace analysis
{
    // compute best polynomial fit
    void polyfit_method(const std::map<std::string, FUNCTION> &fs, const arguments &args)
    {
        std::cout << "\tpolyfit..." << std::endl;
        polyfit pf(args);

        // compute correlation of every function
        std::cout << "\t\tsingle function..." << std::endl;
        for (const std::pair<std::string, FUNCTION> &f : fs)
            pf.compute(f.second, POLYFIT_MAX_DEGREE, f.first);
        pf.save("polyfit", "single");

        // compute cross correlation between every pair
        std::cout << "\t\tcross correlation..." << std::endl;
        for (const std::pair<std::string, FUNCTION> &f : fs)
            for (const std::pair<std::string, FUNCTION> &g : fs)
            {
                if (f.first == g.first)
                    continue;

                DOMAIN d = get_codomain(f.second);
                CODOMAIN c = get_codomain(g.second);
                FUNCTION cross_f = get_function(d, c);
                pf.compute(cross_f, POLYFIT_MAX_DEGREE, f.first + "_+_" + g.first);
            }
        pf.save("polyfit", "cross");
    }

    // compute fft of every dataset and peaks of every fft
    std::map<std::string, FUNCTION> fft_and_fft_peaks(const std::map<std::string, FUNCTION> &fs, const arguments &args)
    {
        // map of peaks of every function in fs
        std::map<std::string, FUNCTION> peaks;

        std::cout << "\tfft..." << std::endl;
        fft fft(args);
        for (const std::pair<std::string, FUNCTION> &f : fs)
        {
            fft.compute(f.second, f.first);
            FUNCTION spectrum = fft.get_last_spectrum();
            fft.save("fft");
            std::cout << "\t\tpeaks..." << std::endl;
            fft_peaks fft_peaks(spectrum, args);
            fft_peaks.compute(f.first);
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
    void rt_fft_and_fft_peaks(const std::map<std::string, FUNCTION> &fs, const arguments &args)
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

    void all_methods(const std::map<std::string, FUNCTION> &fs, const arguments &args)
    {
        std::filesystem::create_directory(args.output);

        polyfit_method(fs, args);                                            // OK: tested!
        std::map<std::string, FUNCTION> peaks = fft_and_fft_peaks(fs, args); // OK: tested!
        peaks_migration(peaks, args);

        rt_fft_and_fft_peaks(fs, args);
    }
}