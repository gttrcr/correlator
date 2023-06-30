#pragma once

#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>

class fft
{
private:
    struct data
    {
    public:
        std::string name;
        FUNCTION spectrum;
    };

    arguments _args;
    std::vector<data> _data;

public:
    fft(const arguments &args)
    {
        _args = args;
    }

    void compute(const FUNCTION &f, const std::string &name)
    {
        kiss_fft_cpx *in = new kiss_fft_cpx[f.size()];
        kiss_fft_cpx *out = new kiss_fft_cpx[f.size()];
        DOMAIN x = get_domain(f);
        CODOMAIN y = get_codomain(f);
        FDST sample_size;
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
                std::cout << "Warning! Domain is not linear or discretization is not regular" << std::endl;

            FUNCTION spectrum;
            for (unsigned int j = 0; j < (full ? f.size() : (f.size() / 2 + 1)); j++)
            {
                FDST freq = (sampling ? sample_size : 1) * (FDST)(f.size()) / (FDST)j;
                FDST power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                spectrum.push_back(std::pair(freq, power));
            }

            _data.push_back({name, spectrum});
        }

        delete[] in;
        delete[] out;
    }

    // save all computed spectra and clear all _data
    void save(const std::string &output_folder)
    {
        std::filesystem::create_directory(_args.output + "/" + output_folder);
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            std::ofstream of(_args.output + "/" + output_folder + "/" + _data[i].name + ".csv");
            of << "freq,power" << std::endl;
            DOMAIN d = get_domain(_data[i].spectrum);     // frequency
            CODOMAIN c = get_codomain(_data[i].spectrum); // power
            for (unsigned int j = 0; j < d.size(); j++)
                of << d[j] << "," << c[j] << std::endl;
            of.close();
        }

        _data.clear();
    }

    FUNCTION get_last_spectrum()
    {
        return _data[_data.size() - 1].spectrum;
    }
};