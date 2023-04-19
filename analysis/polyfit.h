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
    static void _polyfit(const std::vector<default_type> &x, const std::vector<default_type> &y, std::vector<default_type> &coeff, const unsigned int &order)
    {
        Eigen::MatrixXd T(x.size(), order + 1);
        Eigen::VectorXd V = Eigen::VectorXd::Map(&y.front(), y.size());
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
    static void pf(const function &f, const unsigned int &order, const std::string &output_name)
    {
        std::ofstream output_file("output/" + output_name + ".csv");
        output_file << "degree,r^2,";
        for (unsigned int i = 0; i < order; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;

        for (unsigned int ord = 0; ord < order; ord++)
        {
            std::vector<default_type> x = get_domain(f);
            std::vector<default_type> y = get_codomain(f);
            std::vector<default_type> c;
            _polyfit(x, y, c, ord);
            default_type r2 = statistics::get_r2(x, y, c);
            output_file << ord << "," << r2 << ",";
            for (unsigned int o = 0; o < c.size(); o++)
                output_file << c[o] << ",";
            output_file << std::endl;
        }

        output_file.close();
    }

    static void pf(const std::map<std::string, function> &fs, const unsigned int &order, const std::string &output_name)
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

                    std::vector<default_type> x = get_domain(f1.second);
                    std::vector<default_type> y = get_codomain(f2.second);
                    std::vector<default_type> c;
                    _polyfit(x, y, c, ord);
                    default_type r2 = statistics::get_r2(x, y, c);
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