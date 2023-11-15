#pragma once

#include "cli.h"

#include <iostream>

struct arguments
{
private:
    static std::vector<std::string> _default_input() { return {"."}; };
    static std::string _default_output() { return "out_correlator"; }
    static unsigned int _default_domain_size() { return 1; }
    static bool _default_compute_polyfit() { return true; }
    static bool _default_compute_fft() { return true; }

    static unsigned int _default_polyfit_max_degree() { return 5; }
    static double _default_fft_delta_t() { return 0.0; }
    static unsigned int _default_fft_peaks_to_compute() { return 5; }

    void _compute_all()
    {
        compute_polyfit = true;
        compute_fft = true;
    }

    static void _help()
    {
        std::cout << "Correlator helper" << std::endl;
        std::cout << "\t-i: input file or folder. type: string. default: " << _default_input()[0] << std::endl;
        std::cout << "\t-o: output folder. type: string. default: " << _default_output() << std::endl;
        std::cout << "\t-d: domain size of the dataset (in columns). type: unsigned int. default: " << _default_domain_size() << std::endl;
        std::cout << "\t-h: print this help. type: none. default: none" << std::endl;
        std::cout << "\t--pf: compute polynomial fit. type: boolean. default: " << _default_compute_polyfit() << std::endl;
        std::cout << "\t--fft: compute fast Fourier transform. type: boolean. default: " << _default_compute_fft() << std::endl;
        std::cout << "\t--pfdeg: number of max degree for polyfit. type: unsigned int. default: " << _default_polyfit_max_degree() << std::endl;
        std::cout << "\t--fftt: Δt between two entries. type: double. default: computed when possible" << std::endl;
        std::cout << "\t--fftp: number of peaks to compute for every fft. type: unsigned int. default: " << _default_fft_peaks_to_compute() << std::endl;
        std::cout << "\t--help: print this help. type: none. default: none" << std::endl;
    }

public:
    // generic arguments
    std::vector<std::string> input = _default_input(); // -i input file or folder
    std::string output = _default_output();            // -o output folder for -i input
    unsigned int domain_size = _default_domain_size(); // -d domain size in column
    bool compute_polyfit = _default_compute_polyfit(); // --pf compute polyfit (pf is the alias for polyfit)
    bool compute_fft = _default_compute_fft();         // --fft compute fft

    // specific arguments
    unsigned int polyfit_max_degree = _default_polyfit_max_degree();     // --pfdeg number of max degree for polyfit
    double fft_delta_t = _default_fft_delta_t();                         //--fftt Δt between two entries
    unsigned int fft_peaks_to_compute = _default_fft_peaks_to_compute(); // --fftp number of peaks to compute in fft_peaks

    // from argc and argv, create arguments struct
    static arguments get_arguments(int argc, char *argv[])
    {
        arguments args;
        std::map<std::string, std::vector<std::string>> complete_args = get_cli(argc, argv);
        if (complete_args.find("-h") != complete_args.end() || complete_args.find("--help") != complete_args.end())
            _help();

        for (const auto &pair : complete_args)
        {
            if (pair.first == "-i" && pair.second.size() > 0 && !pair.second[0].empty())
            {
                args.input.clear();
                args.input.insert(args.input.end(), pair.second.begin(), pair.second.end());
            }

            if (pair.first == "-o" && pair.second.size() == 1 && !pair.second[0].empty())
                args.output = pair.second[0];

            if (pair.first == "-d" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.domain_size = std::stoi(pair.second[0]);

            if (pair.first == "--pf" && pair.second.size() == 0)
                args.compute_polyfit = true;

            if (pair.first == "--fft" && pair.second.size() == 0)
                args.compute_fft = true;

            if (pair.first == "--all" && pair.second.size() == 0)
                args._compute_all();

            if (pair.first == "--pfdeg" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.polyfit_max_degree = std::stoi(pair.second[0]);

            if (pair.first == "--fftt" && pair.second.size() == 1 && utils::is_number(pair.second[0]))
                args.fft_delta_t = std::stod(pair.second[0]);

            if (pair.first == "--fftp" && pair.second.size() == 1 && utils::is_integer(pair.second[0]))
                args.fft_peaks_to_compute = std::stoi(pair.second[0]);
        }

        if (!args.compute_polyfit && !args.compute_fft)
            args._compute_all();

        return args;
    }
};