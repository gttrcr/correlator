#pragma once

#include "../function.h"
#include "../arguments.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <execution>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <chrono>
#include <thread>
#include <array>
#include <new>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <new>
#include <thread>

namespace analysis
{
    class pattern_matching
    {
    private:
        arguments _args;

        void _ranges(const corr_function small, const corr_function big, const unsigned int small_from, const unsigned int small_to, const unsigned int big_from, const unsigned int big_to)
        {
            corr_function s = small.range(small_from, small_to);
            corr_function b = big.range(big_from, big_to);
            // std::cout << "small [" << small_from << "," << small_to << "] big [" << big_from << "," << big_to << "]" << std::endl;
        }

        void _pattern_matching(const corr_function &f1, const corr_function &f2)
        {
            alignas(std::hardware_destructive_interference_size) corr_function small(f1.size() == max_window ? f1 : f2);
            std::vector<unsigned int> parallelizable_w(1000);
            std::iota(std::begin(parallelizable_w), std::end(parallelizable_w), 0);
            std::for_each(std::execution::par, parallelizable_w.begin(), parallelizable_w.end(), [](unsigned int w)
                          {
                std::cout << w << std::endl;
            const unsigned int max_window = std::min(f1.size(), f2.size());
            corr_function big(f1.size() == max_window ? f2 : f1);
            const unsigned int min_window = 2;
            unsigned int big_size = big.size();
                for (unsigned int w = 0; w < max_window; w++)
                for (int i = max_window - 1; i >= (int)(w + min_window - 1); i--)
                {
                    const unsigned int width = i - w + 1;
                    for (unsigned int j = 0; j <= big_size - width; j++)
                        ; //_ranges(small, big, w, i, j, j + width - 1);
                              } });
        }

    public:
        pattern_matching(const arguments &args)
        {
            _args = args;
        }

        void compute(const corr_function &f)
        {
            _pattern_matching(f, f);
        }

        void save()
        {
        }
    };
}