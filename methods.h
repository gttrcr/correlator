#pragma once

#include "statistics.h"
#include "kissfft/kiss_fft.h"
#include "results.h"

#include <vector>
#include <iomanip>

#define THREASHOLD 0.9

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::vector<T_SPACE>> power(const std::vector<function<domain_size, codomain_size>> &fs, const T_SPACE &p)
{
    std::vector<std::vector<T_SPACE>> rets;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        for (unsigned int j = i + 1; j < fs.size(); j++)
        {
            T_SPACE ps = pearson(fs[i], fs[j].pow(p));
            if (ps > THREASHOLD)
            {
                std::vector<T_SPACE> ret;
                ret.push_back(p);
                ret.push_back(i);
                ret.push_back(j);
                ret.push_back(ps);
                rets.push_back(ret);
                std::cout << p << i << " " << j << " " << ps << std::endl;
            }
        }
    }

    return rets;
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::vector<T_SPACE>> log(const std::vector<function<domain_size, codomain_size>> &fs)
{
    std::vector<std::vector<T_SPACE>> rets;
    for (unsigned int i = 0; i < fs.size(); i++)
    {
        for (unsigned int j = i + 1; j < fs.size(); j++)
        {
            T_SPACE ps = pearson(fs[i], fs[j].log());
            if (ps > THREASHOLD)
            {
                std::vector<T_SPACE> ret;
                ret.push_back(i);
                ret.push_back(j);
                ret.push_back(ps);
                rets.push_back(ret);
                std::cout << i << " " << j << " " << ps << std::endl;
            }
        }
    }

    return rets;
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<std::vector<std::tuple<T_SPACE, T_SPACE>>> fft(const std::vector<function<domain_size, codomain_size>> &fs)
{
    std::vector<std::vector<std::tuple<T_SPACE, T_SPACE>>> ret_peaks;
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
            std::vector<std::tuple<T_SPACE, T_SPACE>> power_spectrum;
            for (unsigned int j = 0; j < (full ? fs[i].size() : fs[i].size() / 2 + 1); j++)
            {
                T_SPACE f = (T_SPACE)fs[i].size() / (T_SPACE)j;
                T_SPACE p = sqrt(pow(out[j].i, 2) + pow(out[j].r, 2));
                std::cout << f << " " << p << std::endl;
                power_spectrum.push_back(std::make_tuple(f, p));
            }

            std::vector<std::tuple<T_SPACE, T_SPACE>> peak = peaks(power_spectrum, 10);
            ret_peaks.push_back(peak);
        }
        else
            throw std::runtime_error("error on allocating fft");
    }

    return ret_peaks;
}

void migration_of_fft_peaks(const std::vector<std::vector<std::tuple<T_SPACE, T_SPACE>>> &peaks)
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

        // compute fft of vector of fs and return their peaks
        std::vector<std::vector<std::tuple<T_SPACE, T_SPACE>>> peaks = fft(fs);
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