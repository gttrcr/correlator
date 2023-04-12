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

#define THREASHOLD 0.9

// template <unsigned int domain_size, unsigned int codomain_size>
// std::vector<std::vector<T_SPACE>> power(const std::vector<function<domain_size, codomain_size>> &fs, const T_SPACE &p)
//{
//     std::vector<std::vector<T_SPACE>> rets;
//     for (unsigned int i = 0; i < fs.size(); i++)
//     {
//         for (unsigned int j = i + 1; j < fs.size(); j++)
//         {
//             T_SPACE ps = pearson(fs[i], fs[j].pow(p));
//             if (ps > THREASHOLD)
//             {
//                 std::vector<T_SPACE> ret;
//                 ret.push_back(p);
//                 ret.push_back(i);
//                 ret.push_back(j);
//                 ret.push_back(ps);
//                 rets.push_back(ret);
//                 std::cout << p << i << " " << j << " " << ps << std::endl;
//             }
//         }
//     }
//
//     return rets;
// }
//
// template <unsigned int domain_size, unsigned int codomain_size>
// std::vector<std::vector<T_SPACE>> log(const std::vector<function<domain_size, codomain_size>> &fs)
//{
//     std::vector<std::vector<T_SPACE>> rets;
//     for (unsigned int i = 0; i < fs.size(); i++)
//     {
//         for (unsigned int j = i + 1; j < fs.size(); j++)
//         {
//             T_SPACE ps = pearson(fs[i], fs[j].log());
//             if (ps > THREASHOLD)
//             {
//                 std::vector<T_SPACE> ret;
//                 ret.push_back(i);
//                 ret.push_back(j);
//                 ret.push_back(ps);
//                 rets.push_back(ret);
//                 std::cout << i << " " << j << " " << ps << std::endl;
//             }
//         }
//     }
//
//     return rets;
// }

void polyfit(const std::vector<double> &t, const std::vector<double> &v, std::vector<double> &coeff, const unsigned int &order)
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
std::vector<double> polyfit(const function<domain_size, codomain_size> &f1, const function<domain_size, codomain_size> &f2, const unsigned int &order)
{
    std::vector<double> x;
    for (unsigned int i = 0; i < f1.size(); i++)
        x.push_back(f1.get(i, 1));

    std::vector<double> y;
    for (unsigned int i = 0; i < f2.size(); i++)
        y.push_back(f2.get(i, 1));

    std::vector<double> c;
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
            std::vector<double> c = polyfit(fs[i], fs[j], order);
            std::cout << order << " " << i << " " << j << " ";
            for (unsigned int o = 0; o <= order; o++)
                std::cout << c[o] << " ";
            std::cout << std::endl;
        }
    }
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::vector<std::tuple<t_space, t_space>>> fft(const std::vector<function<domain_size, codomain_size>> &fs)
{
    std::vector<std::vector<std::tuple<t_space, t_space>>> ret_peaks;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        kiss_fft_cpx in[fs[i].size()];
        kiss_fft_cpx out[fs[i].size()];
        for (unsigned int j = 0; j < fs[i].size(); j++)
            in[j] = {fs[i].get(j, domain_size), 0};

        kiss_fft_cfg cfg;
        if ((cfg = kiss_fft_alloc(fs[i].size(), 0, NULL, NULL)) != NULL)
        {
            kiss_fft(cfg, in, out);
            free(cfg);
            const bool full = false;
            std::vector<std::tuple<t_space, t_space>> power_spectrum;
            for (unsigned int j = 0; j < (full ? fs[i].size() : fs[i].size() / 2 + 1); j++)
            {
                t_space f = (t_space)fs[i].size() / (t_space)j;
                t_space p = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                std::cout << f << " " << p << std::endl;
                power_spectrum.push_back(std::make_tuple(f, p));
            }

            std::vector<std::tuple<t_space, t_space>> peak = peaks(power_spectrum, 10);
            ret_peaks.push_back(peak);
        }
        else
            throw std::runtime_error("error on allocating fft");
    }

    return ret_peaks;
}

void migration_of_fft_peaks(const std::vector<std::vector<std::tuple<t_space, t_space>>> &peaks)
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
        // results results;
        //  for (T_SPACE p = 1; p < 10; p++)
        //      results.add("power", power(fs, p));
        //
        //  for (T_SPACE p = 1; p < 10; p++)
        //     results.add("power", power(fs, 1 / p));
        //
        //  results.save("power", "method,p,file1,file2,pearson");
        //
        //  results.add("log", log(fs));
        //  results.save("log", "method,file1,file2,pearson");

        for (unsigned int i = 0; i < 10; i++)
            polyfit(fs, i);

        // compute fft of vector of fs and return their peaks
        std::vector<std::vector<std::tuple<t_space, t_space>>> peaks = fft(fs);
        if (peaks.size() > 1)
            migration_of_fft_peaks(peaks);

        return true;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}