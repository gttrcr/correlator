#pragma once

#include "cli.h"

#include <iostream>

struct arguments
{
public:
    std::vector<std::string> input = {"."};                                                     // -i input file or folder
    std::string output = get_default_output();                                                  // -o output folder for -i input
    unsigned int number_of_fft_peaks_to_compute = get_default_number_of_fft_peaks_to_compute(); // -e number of peaks to compute in fft_peaks
    unsigned int domain_size = get_default_domain_size();                                       // -d domain size
    unsigned int polyfit_max_degree = get_polyfit_max_degree();                                 // -f number of max degree for polyfit
    bool compute_polyfit = get_default_compute_polyfit();                                       // --polyfit compute polyfit
    bool compute_fft = get_default_compute_fft();                                               // --fft compute fft
    bool compute_fft_peaks = get_default_compute_fft_peaks();                                   // --fftp compute fft peaks
    bool compute_fft_peaks_migration = get_default_compute_fft_peaks_migration();               // --fftpm compute fft peaks migration

    // from argc and argv, create arguments struct
    static arguments get_arguments(int argc, char *argv[])
    {
        arguments args;
        std::map<std::string, std::vector<std::string>> complete_args = get_cli(argc, argv);
        for (const auto &pair : complete_args)
        {
            if (pair.first == "-i" && pair.second.size() > 0 && !pair.second[0].empty())
            {
                args.input.clear();
                args.input.insert(args.input.end(), pair.second.begin(), pair.second.end());
            }

            if (pair.first == "-o" && pair.second.size() == 1 && !pair.second[0].empty())
                args.output = pair.second[0];

            if (pair.first == "-e" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.number_of_fft_peaks_to_compute = std::stoi(pair.second[0]);

            if (pair.first == "-d" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.domain_size = std::stoi(pair.second[0]);

            if (pair.first == "-f" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.polyfit_max_degree = std::stoi(pair.second[0]);

            if (pair.first == "--polyfit" && pair.second.size() == 0)
                args.compute_polyfit = true;

            if (pair.first == "--fft" && pair.second.size() == 0)
                args.compute_fft = true;

            if (pair.first == "--fftp" && pair.second.size() == 0)
                args.compute_fft_peaks = true;

            if (pair.first == "--fftpm" && pair.second.size() == 0)
                args.compute_fft_peaks_migration = true;

            if (pair.first == "--all" && pair.second.size() == 0)
                args.compute_all();
        }

        if (!args.compute_polyfit && !args.compute_fft && !args.compute_fft_peaks && !args.compute_fft_peaks_migration)
            args.compute_all();

        return args;
    }

private:
    static std::string get_default_output() { return "out_correlator"; }
    static unsigned int get_default_number_of_fft_peaks_to_compute() { return 5; }
    static unsigned int get_default_domain_size() { return 1; }
    static unsigned int get_polyfit_max_degree() { return 5; }
    static bool get_default_compute_polyfit() { return false; }
    static bool get_default_compute_fft() { return false; }
    static bool get_default_compute_fft_peaks() { return false; }
    static bool get_default_compute_fft_peaks_migration() { return false; }

    void compute_all()
    {
        compute_polyfit = true;
        compute_fft = true;
        compute_fft_peaks = true;
        compute_fft_peaks_migration = true;
    }
};