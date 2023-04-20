#pragma once

#include "../function.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include "../statistics.h"

#include <fstream>
#include <map>

class polyfit
{
private:
    template <typename T>
    static std::vector<double> to_double(const std::vector<T> &v)
    {
        std::vector<double> ret;
        for (unsigned int i = 0; i < v.size(); i++)
            ret.push_back((double)v[i]);

        return ret;
    }

    static void _polyfit(const std::vector<ddt> &x, const std::vector<cdt> &y, std::vector<cdt> &coeff, const unsigned int &order)
    {
        std::vector<double> y_double = to_double(y);
        Eigen::MatrixXd T(x.size(), order + 1);
        Eigen::VectorXd V = Eigen::VectorXd::Map(&y_double.front(), y_double.size());
        Eigen::VectorXd result;

        assert(x.size() == y.size());
        assert(x.size() >= order + 1);

        for (size_t i = 0; i < x.size(); ++i)
            for (size_t j = 0; j < order + 1; ++j)
                T(i, j) = pow(x.at(i), j);

        result = T.householderQr().solve(V);
        coeff.resize(order + 1);
        for (unsigned int k = 0; k < order + 1; k++)
            coeff[k] = result[k];
    }

public:
    static void compute(const function &f, const unsigned int &order, const std::string &output_name)
    {
        std::ofstream output_file("output/" + output_name + ".csv");
        output_file << "degree,r^2,";
        for (unsigned int i = 0; i < order; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;

        for (unsigned int ord = 0; ord < order; ord++)
        {
            std::vector<ddt> x = get_domain(f);
            std::vector<cdt> y = get_codomain(f);
            std::vector<cdt> c;
            _polyfit(x, y, c, ord);
            cdt r2 = statistics::get_r2(x, y, c);
            output_file << ord << "," << r2 << ",";
            for (unsigned int o = 0; o < c.size(); o++)
                output_file << c[o] << ",";
            output_file << std::endl;
        }

        output_file.close();
    }

    static void compute(const std::map<std::string, function> &fs, const unsigned int &order, const std::string &output_name)
    {
        std::ofstream output_file("output/" + output_name + ".csv");
        output_file << "degree,r^2,f1,f2,";
        for (unsigned int i = 0; i < order; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;

        for (unsigned int ord = 0; ord < order; ord++)
        {
            for (const std::pair<std::string, function> f1 : fs)
            {
                for (const std::pair<std::string, function> f2 : fs)
                {
                    if (f1.first == f2.first)
                        continue;

                    std::vector<ddt> x = get_domain(f1.second);
                    std::vector<cdt> y = get_codomain(f2.second);
                    std::vector<cdt> c;
                    _polyfit(x, y, c, ord);
                    cdt r2 = statistics::get_r2(x, y, c);
                    output_file << ord << "," << r2 << "," << f1.first << "," << f2.first << ",";
                    for (unsigned int o = 0; o < c.size(); o++)
                        output_file << c[o] << ",";
                    output_file << std::endl;
                }
            }
        }

        output_file.close();
    }
};