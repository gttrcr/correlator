#pragma once

#include <vector>
#include <map>

namespace analysis
{
    class entropy
    {
    private:
        std::vector<double> _data;

    public:
        double compute(const std::vector<double> &data)
        {
            return 0.3;
        }

        double step(const double &data)
        {
            std::map<long long int, unsigned int> count;
            const double sigma = 0.0001;
            _data.push_back(data);
            for (unsigned int i = 0; i < _data.size(); i++)
                count[(long long int)(_data[i] / sigma)]++;

            double entropy = 0;
            for (std::map<long long int, unsigned int>::iterator it = count.begin(); it != count.end(); it++)
            {
                double p = (double)it->second / (double)_data.size();
                entropy += p * log(p);
            }

            return -entropy;
        }
    };
}