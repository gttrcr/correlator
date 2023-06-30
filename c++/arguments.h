#pragma once

#include <iostream>

struct arguments
{
public:
    unsigned int port = 0;                                                                      // port for socket connection (-p)
    std::string input = ".";                                                                    // input file or folder (-i)
    std::string output = get_default_output();                                                  // output folder for -i input (-o)
    std::string socket_output = get_default_socket_output();                                    // output folder for socket correlation (-s)
    unsigned int number_of_fft_peaks_to_compute = get_default_number_of_fft_peaks_to_compute(); // number of peaks to compute in fft_peaks (-e)
    unsigned int codomain_column_index = get_default_codomain_column_index();                   // index of the column in the codomain scope to use in correlator (-c)
    unsigned int domain_size = get_default_domain_size();                                       // domain size (-d)
    unsigned int polyfit_max_degree = get_polyfit_max_degree();                                 // number od max degree for polyfit (-f)

    static unsigned int get_default_port() { return 39785; }

private:
    static std::string get_default_output() { return "out_correlator"; }

    static std::string get_default_socket_output() { return "socket_out_correlator"; }

    static unsigned int get_default_number_of_fft_peaks_to_compute() { return 5; }

    static unsigned int get_default_codomain_column_index() { return 1; }

    static unsigned int get_default_domain_size() { return 1; }

    static unsigned int get_polyfit_max_degree() { return 5; }
};