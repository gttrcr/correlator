#pragma once

#include "cli.h"
#include "json.hpp"

#include <iostream>
#include <optional>
using json = nlohmann::json;

struct help
{
public:
    std::string command;                      // command string
    std::string description;                  // description of the command
    bool mandatory;                           // if its value is mandatory, the program will not be executed without it
    std::optional<std::string> type;          // type of its value
    std::optional<bool> multiple;             // the command can have multiple values
    std::optional<std::string> default_value; // the default value
};

struct arguments
{
private:
    static std::vector<std::string> _default_input() { return {"."}; };
    static std::string _default_output() { return "out_correlator"; }
    static std::vector<unsigned int> _default_domain_indexes() { return {0}; }
    static bool _default_merge() { return false; }
    static bool _default_compute_polyfit() { return true; }
    static bool _default_compute_fft() { return true; }

    static unsigned int _default_polyfit_max_degree() { return 5; }
    static double _default_fft_delta_t() { return 0.0; }
    static unsigned int _default_fft_peaks_to_compute() { return 5; }

    static std::vector<help> help_vector()
    {
        std::vector<help> csv;
        csv.push_back({"-i", "input file or folder", false, "string", true, _default_input()[0]});
        csv.push_back({"-o", "output folder", false, "string", false, _default_output()});
        csv.push_back({"-d", "domain columns index of the dataset", false, "unsigned int", true, std::to_string(_default_domain_indexes()[0])});
        csv.push_back({"-m", "merge domain columns from multiple files", false});
        csv.push_back({"-h", "print this help", false});
        csv.push_back({"-j", "print this help in json format", false});
        csv.push_back({"--pf", "compute polynomial fit", false});
        csv.push_back({"--fft", "compute Fast Fourier Transform", false});
        csv.push_back({"--pfdeg", "number of max degree for polyfit", false, "unsigned int", false, std::to_string(_default_polyfit_max_degree())});
        csv.push_back({"--fftt", "Δt between two entries", false, "double", false, std::to_string(_default_fft_delta_t())});
        csv.push_back({"--fftp", "number of peaks to compute for every fft", false, "unsigned int", false, std::to_string(_default_fft_peaks_to_compute())});

        return csv;
    }

    static void _help()
    {
        std::vector<help> help = help_vector();
        std::cout << "Correlator helper" << std::endl;
        for (unsigned int i = 0; i < help.size(); i++)
        {
            std::cout << "\tCommand\t\t" << help[i].command << std::endl;
            std::cout << "\tDescription\t" << help[i].description << std::endl;
            std::cout << "\tMandatory\t" << help[i].mandatory << std::endl;
            if (help[i].type.has_value())
                std::cout << "\tType\t\t" << help[i].type.value() << std::endl;
            if (help[i].multiple.has_value())
                std::cout << "\tMultiple\t" << help[i].multiple.value() << std::endl;
            if (help[i].default_value.has_value())
                std::cout << "\tDefault value\t" << help[i].default_value.value() << std::endl;
            std::cout << "--------------------" << std::endl;
        }
    }

    static void _json_help()
    {
        json json_help;
        std::vector<help> help = help_vector();
        for (unsigned int i = 0; i < help.size(); i++)
        {
            json command;
            command["command"] = help[i].command;
            command["description"] = help[i].description;
            command["mandatory"] = help[i].mandatory;
            if (help[i].type.has_value())
                command["type"] = help[i].type.value();
            if (help[i].multiple.has_value())
                command["multiple"] = help[i].multiple.value();
            if (help[i].default_value.has_value())
                command["default_value"] = help[i].default_value.value();
            json_help[i] = command;
        }

        std::cout << json_help.dump(4) << std::endl;
    }

public:
    // generic arguments
    std::vector<std::string> input = _default_input();                    // -i input file or folder
    std::string output = _default_output();                               // -o output folder for -i input
    std::vector<unsigned int> domain_indexes = _default_domain_indexes(); // -d domain columns index
    bool merge = _default_merge();                                        // -m merge domain columns from multiple files
    bool compute_polyfit = _default_compute_polyfit();                    // --pf compute polyfit (pf is the alias for polyfit)
    bool compute_fft = _default_compute_fft();                            // --fft compute fft

    // specific arguments
    unsigned int polyfit_max_degree = _default_polyfit_max_degree();     // --pfdeg number of max degree for polyfit
    double fft_delta_t = _default_fft_delta_t();                         // --fftt Δt between two entries
    unsigned int fft_peaks_to_compute = _default_fft_peaks_to_compute(); // --fftp number of peaks to compute in fft_peaks

    // from argc and argv, create arguments struct
    static bool get_arguments(int argc, char *argv[], arguments &args)
    {
        std::map<std::string, std::vector<std::string>> complete_args = get_cli(argc, argv);
        if (complete_args.find("-h") != complete_args.end() || complete_args.find("--help") != complete_args.end())
        {
            _help();
            return false;
        }

        if (complete_args.find("-j") != complete_args.end())
        {
            _json_help();
            return false;
        }

        for (const auto &pair : complete_args)
        {
            //-i command && more then 0 argument && ??
            if (pair.first == "-i")
            {
                if (pair.second.size() > 0 && !pair.second[0].empty())
                {
                    args.input.clear();
                    args.input.insert(args.input.end(), pair.second.begin(), pair.second.end());
                }
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //-o command && exactly one argument && not empty argument
            if (pair.first == "-o")
            {
                if (pair.second.size() == 1 && !pair.second[0].empty())
                    args.output = pair.second[0];
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //-d command && more than 0 argument && all arguments are integers
            if (pair.first == "-d")
            {
                if (pair.second.size() > 0 && std::all_of(pair.second.begin(), pair.second.end(), [](std::string i)
                                                          { return utils::is_positive_integer(i); }))
                {
                    args.domain_indexes.clear();
                    std::vector<unsigned int> domain_parsed;
                    for (unsigned int i = 0; i < pair.second.size(); i++)
                        domain_parsed.push_back(std::stoi(pair.second[i]));
                    args.domain_indexes.insert(args.domain_indexes.end(), domain_parsed.begin(), domain_parsed.end());
                }
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //-m command && no arguments
            if (pair.first == "-m")
            {
                if (pair.second.size() == 0)
                    args.merge = true;
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //--pf command && no arguments
            if (pair.first == "--pf")
            {
                if (pair.second.size() == 0)
                    args.compute_polyfit = true;
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //--fft command && no arguments
            if (pair.first == "--fft")
            {
                if (pair.second.size() == 0)
                    args.compute_fft = true;
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //--pfdeg command && exactly one argument && argument is integer
            if (pair.first == "--pfdeg")
            {
                if (pair.second.size() == 1 && utils::is_positive_integer(pair.second[0]))
                    args.polyfit_max_degree = std::stoi(pair.second[0]);
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //--fftt command && exactly one argument && argument is integer
            if (pair.first == "--fftt")
            {
                if (pair.second.size() == 1 && utils::is_number(pair.second[0]))
                    args.fft_delta_t = std::stod(pair.second[0]);
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }

            //--fftp command && exactly one argument && argument is integer
            if (pair.first == "--fftp")
            {
                if (pair.second.size() == 1 && utils::is_positive_integer(pair.second[0]))
                    args.fft_peaks_to_compute = std::stoi(pair.second[0]);
                else
                    std::cerr << "Something wrong with command " << pair.first << std::endl;
            }
        }

        return true;
    }
};