#pragma once

#include "computable.h"

#include <vector>
#include <map>

namespace analysis
{
    class entropy : public computable<std::vector<double>, int, int,
                                      double, int, int,
                                      double, double>
    {
    private:
        constexpr static const double _sigma = 0.000001;
        std::map<long long int, unsigned int> _count;
        unsigned int _n = 0;

        static double _entropy(const std::map<long long int, unsigned int> &count, const unsigned int n)
        {
            double entropy = 0;
            for (const auto &el : count)
            {
                double p = (double)el.second / (double)n;
                entropy += p * log(p);
            }

            return -entropy;
        }

    public:
        static double compute(const std::vector<double> &data)
        {
            std::map<long long int, unsigned int> count;
            for (unsigned int i = 0; i < data.size(); i++)
                count[(long long int)(data[i] / _sigma)]++;

            return _entropy(count, data.size());
        }

        double step(const double &data)
        {
            _n++;
            _count[(long long int)(data / _sigma)]++;

            return _entropy(_count, _n);
        }

        void clear()
        {
            _n = 0;
            _count.clear();
        }
    };
}