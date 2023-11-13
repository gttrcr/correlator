#pragma once

#include "../function.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include "../statistics.h"
#include "../utils.h"

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <optional>
#ifdef THREAD_SUPPORT
#include <mutex>
#endif

namespace analysis
{
    class polyfit
    {
    private:
        struct data
        {
        public:
            unsigned int degree;
            FDST r2;
            SOURCE source1;
            std::optional<SOURCE> source2;
            codomain coeff;
        };

        arguments _args;
        std::vector<data> _data;
#ifdef THREAD_SUPPORT
        std::mutex _mtx;
#endif

        void _polyfit(const domain &x, const codomain &y, codomain &coeff, const unsigned int &degree)
        {
            Eigen::MatrixXd T(x.size(), degree + 1);
            Eigen::VectorXd V = Eigen::VectorXd::Map(&y.front(), y.size());
            Eigen::VectorXd result;

            assert(x.size() == y.size());
            assert(x.size() >= degree + 1);

            for (size_t i = 0; i < x.size(); ++i)
                for (size_t j = 0; j < degree + 1; ++j)
                    T(i, j) = pow(x[i], j);

            result = T.householderQr().solve(V);
            coeff.resize(degree + 1);
            for (unsigned int k = 0; k < degree + 1; k++)
                coeff[k] = result[k];
        }

    public:
        polyfit(const arguments &args)
        {
            _args = args;
        }

        void compute(const corr_function &f, const unsigned int &degree, const SOURCE &source1, const std::optional<SOURCE> &source2 = std::nullopt)
        {
            std::vector<data> tmp_data;
            for (unsigned int deg = 0; deg <= degree; deg++)
            {
                domain x = f.get_domain();
                codomain y = f.get_codomain();
                codomain c;
                _polyfit(x, y, c, deg);
                FDST r2 = statistics::get_r2(x, y, c);
                tmp_data.push_back({deg, r2, source1, source2, c});
            }

            std::sort(tmp_data.begin(), tmp_data.end(), [](const data &d1, const data &d2)
                      { return d1.r2 > d2.r2; });

#ifdef THREAD_SUPPORT
            _mtx.lock();
#endif
            _data.insert(_data.end(), tmp_data.begin(), tmp_data.end());
#ifdef THREAD_SUPPORT
            _mtx.unlock();
#endif
        }

        // save all computed correlation and clear all _data
        void save(const std::string &output_folder, const std::string &output_file)
        {
            // remove nan or inf elements
            _data.erase(std::remove_if(_data.begin(), _data.end(), [](const data &d)
                                       { return std::isnan(d.r2) || std::isinf(d.r2); }),
                        _data.end());

            // create the output csv
            std::filesystem::create_directory(_args.output + "/" + output_folder);
            std::ofstream of(_args.output + "/" + output_folder + "/" + output_file);
            of << "degree,r^2,file1,column1,";
            if (_data.size() > 0 && _data[0].source2.has_value())
                of << "file2,column2,";

            // get the heighest degree in data
            std::vector<data>::iterator it = std::max_element(_data.begin(), _data.end(), [](const data &d1, const data &d2)
                                                              { return d1.degree < d2.degree; });
            unsigned int degree = (it != _data.end()) ? it->degree : 0;
            for (unsigned int i = 0; i <= degree; i++)
                of << "d" << i << ",";
            of << std::endl;

            for (unsigned int i = 0; i < _data.size(); i++)
            {
                of << _data[i].degree << "," << _data[i].r2 << "," << _data[i].source1.first << "," << _data[i].source1.second << ",";
                if (_data[i].source2.has_value())
                    of << _data[i].source2.value().first << "," << _data[i].source2.value().second << ",";

                for (unsigned int j = 0; j < _data[i].coeff.size(); j++)
                    of << _data[i].coeff[j] << ",";
                of << std::endl;
            }

            _data.clear();
            of.close();
        }
    };
}