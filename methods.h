#pragma once

#include "statistics.h"
#include "kissfft/kiss_fft.h"
#include "results.h"
#include "eigen/Eigen/Dense"
#include "eigen/Eigen/QR"

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <filesystem>

std::ofstream output_file;

void polyfit(const std::vector<t_space> &t, const std::vector<t_space> &v, std::vector<long_t_space> &coeff, const unsigned int &order)
{
    // Create Matrix Placeholder of size n x k, n= number of datapoints, k = order of polynomial, for exame k = 3 for cubic polynomial
    Eigen::MatrixXd T(t.size(), order + 1);
    Eigen::VectorXd V = Eigen::VectorXd::Map(&v.front(), v.size());
    Eigen::VectorXd result;

    // check to make sure inputs are correct
    assert(t.size() == v.size());
    assert(t.size() >= order + 1);
    // Populate the matrix
    for (size_t i = 0; i < t.size(); ++i)
    {
        for (size_t j = 0; j < order + 1; ++j)
        {
            T(i, j) = pow(t.at(i), j);
        }
    }
    // std::cout << T << std::endl;

    // Solve for linear least square fit
    result = T.householderQr().solve(V);
    coeff.resize(order + 1);
    for (unsigned int k = 0; k < order + 1; k++)
    {
        coeff[k] = result[k];
    }
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<long_t_space> polyfit(const function<domain_size, codomain_size> &f1, const function<domain_size, codomain_size> &f2, const unsigned int &order)
{
    std::vector<t_space> x;
    for (unsigned int i = 0; i < f1.size(); i++)
        x.push_back(f1.get(i, 1));

    std::vector<t_space> y;
    for (unsigned int i = 0; i < f2.size(); i++)
        y.push_back(f2.get(i, 1));

    std::vector<long_t_space> c;
    polyfit(x, y, c, order);

    return c;
}

template <unsigned int domain_size, unsigned int codomain_size>
void polyfit(const std::vector<function<domain_size, codomain_size>> &fs, const unsigned int &order)
{
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        for (unsigned int j = i + 1; j < fs.size(); j++)
        {
            std::vector<long_t_space> c = polyfit(fs[i], fs[j], order);
            output_file << order << "," << i << "," << j << ",";
            for (unsigned int o = 0; o <= order; o++)
                output_file << c[o] << ",";
            output_file << std::endl;
        }
    }
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<function<1, 1>> fft(const std::vector<function<domain_size, codomain_size>> &fs)
{
    std::vector<function<1, 1>> ret_peaks;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        kiss_fft_cpx in[fs[i].size()];
        kiss_fft_cpx out[fs[i].size()];
        long_t_space sampling_time = fs[i].get(1, 0) - fs[i].get(0, 0);
        for (unsigned int j = 0; j < fs[i].size(); j++)
        {
            in[j] = {(kiss_fft_scalar)fs[i].get(j, domain_size), 0};
            if (sampling_time != 0 && j > 0 && std::fabs(sampling_time - (fs[i].get(j, 0) - fs[i].get(j - 1, 0))) > 100 * std::numeric_limits<t_space>::epsilon())
                sampling_time = 0;
        }

        kiss_fft_cfg cfg;
        if ((cfg = kiss_fft_alloc(fs[i].size(), 0, NULL, NULL)) != NULL)
        {
            kiss_fft(cfg, in, out);
            free(cfg);
            const bool full = false;
            if (sampling_time == 0)
                std::cout << "Warning! sampling time is 0: time is not linear or interfals are not regular" << std::endl;
            function<1, 1> power_spectrum;
            for (unsigned int j = 0; j < (full ? fs[i].size() : (fs[i].size() / 2 + 1)); j++)
            {
                long_t_space f = (sampling_time == 0 ? 1 : sampling_time) * (long_t_space)fs[i].size() / (long_t_space)j;
                long_t_space p = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                std::cout << f << " " << p << std::endl;
                power_spectrum.set(domain<1>(f), codomain<1>(p));
            }

            ret_peaks.push_back(peaks(power_spectrum, 5));
        }
        else
            throw std::runtime_error("error on allocating fft");
    }

    return ret_peaks;
}

void migration_of_fft_peaks(const std::vector<std::vector<std::tuple<long_t_space, long_t_space>>> &peaks)
{
    for (unsigned int i = 0; i < peaks.size(); i++)
    {
        unsigned int a = 0;
    }
}

template <unsigned int domain_size, unsigned int codomain_size>
bool methods(const std::vector<function<domain_size, codomain_size>> &fs)
{
    try
    {
        std::filesystem::create_directory("output");

        // compute best polynomial fit until nth degree
        const unsigned int n = 15;
        output_file.open("output/polynomial_fit.csv");
        output_file << "degree,f1,f2,";
        for (unsigned int i = 0; i < n; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;
        for (unsigned int i = 0; i < n; i++)
            polyfit(fs, i);
        output_file.close();

        // compute fft of vector of fs and return their peaks
        output_file.open("output/fft.csv");
        std::vector<function<1, 1>> peaks = fft(fs);
        if (peaks.size() > 1)
        {
        }
        output_file.close();

        return true;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}