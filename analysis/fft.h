#pragma once

#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include <iostream>
#include <map>
#include <fstream>

class fft
{
private:
    arguments _args;
    function _spectrum;

public:
    fft(const arguments &args)
    {
        _args = args;
    }

    bool compute(const function &f, const std::string &name = "")
    {
        kiss_fft_cpx in[f.size()];
        kiss_fft_cpx out[f.size()];
        std::vector<ddt> x = get_domain(f);
        std::vector<cdt> y = get_codomain(f);
        ddt sample_size;
        bool sampling = get_sampling(f, sample_size);
        for (unsigned int i = 0; i < f.size(); i++)
            in[i] = {(kiss_fft_scalar)y[i], 0};

        kiss_fft_cfg cfg;
        if ((cfg = kiss_fft_alloc(f.size(), 0, NULL, NULL)) != NULL)
        {
            kiss_fft(cfg, in, out);
            free(cfg);
            const bool full = false;
            if (!sampling)
                std::cout << "Warning! Time is not linear or intervals are not regular" << std::endl;

            _spectrum.clear();
            for (unsigned int j = 0; j < (full ? f.size() : (f.size() / 2 + 1)); j++)
            {
                ddt freq = (sampling ? sample_size : 1) * (ddt)(f.size()) / (ddt)j;
                cdt power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                _spectrum.push_back(std::pair(freq, power));
            }

            if (!name.empty())
            {
                std::ofstream output_file(_args.output + "/fft_" + name);
                output_file << "freq,power" << std::endl;
                domain d = get_domain(_spectrum);     // frequency
                codomain c = get_codomain(_spectrum); // power
                for (unsigned int i = 0; i < d.size(); i++)
                    output_file << d[i] << "," << c[i] << std::endl;
                output_file.close();
            }
        }
        else
            return false;

        return true;
    }

    function get_spectrum()
    {
        return _spectrum;
    }
};