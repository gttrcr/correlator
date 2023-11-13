#pragma once

#include "../kissfft/kiss_fft.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"
#include "result.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace analysis
{
    class fft
    {
    private:
        struct data
        {
        public:
            SOURCE source;
            corr_function spectrum;
        };

        arguments _args;
        data _data;

    public:
        fft(const arguments &args)
        {
            _args = args;
        }

        void compute(const corr_function &f, const SOURCE &source)
        {
            kiss_fft_cpx *in = new kiss_fft_cpx[f.size()];
            kiss_fft_cpx *out = new kiss_fft_cpx[f.size()];
            // domain x = f.get_domain();
            codomain y = f.get_codomain();
            FDST sample_size;
            bool sampling = f.get_sampling(sample_size);
            for (unsigned int i = 0; i < f.size(); i++)
                in[i] = {(kiss_fft_scalar)y[i], 0};

            kiss_fft_cfg cfg;
            if ((cfg = kiss_fft_alloc(f.size(), 0, NULL, NULL)) != NULL)
            {
                kiss_fft(cfg, in, out);
                free(cfg);
                const bool full = false;
                if (!sampling)
                    std::cerr << "Warning! Domain is not linear or discretization is not regular" << std::endl; // TODO add discretization here

                corr_function spectrum;
                for (unsigned int j = 0; j < (full ? f.size() : (f.size() / 2 + 1)); j++)
                {
                    FDST freq = (sampling ? sample_size : 1) * (FDST)(f.size()) / (FDST)j;
                    FDST power = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                    spectrum.push_back(freq, power);
                }

                _data = {source, spectrum};
            }

            delete[] in;
            delete[] out;
        }

        // save all computed spectra and clear all _data
        void save(const std::string &output_folder, const std::string &output_file) const
        {
            std::filesystem::create_directory(_args.output + "/" + output_folder);
            std::ofstream of(_args.output + "/" + output_folder + "/" + output_file);
            analysis::metadata::get()->set_analysis(output_folder, output_file);
            of << "freq,power" << std::endl;
            domain d = _data.spectrum.get_domain();     // frequency
            codomain c = _data.spectrum.get_codomain(); // power
            for (unsigned int j = 0; j < d.size(); j++)
                of << d[j] << "," << c[j] << std::endl;
            of.close();
        }

        corr_function get_spectrum() const
        {
            return _data.spectrum;
        }
    };
}