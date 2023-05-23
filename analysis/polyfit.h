#pragma once

#include "../function.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include "../statistics.h"
#include "../utils.h"

#include <fstream>
#include <map>

class polyfit
{
private:
    arguments _args;

    void _polyfit(const std::vector<ddt> &x, const std::vector<cdt> &y, std::vector<cdt> &coeff, const unsigned int &order)
    {
        std::vector<double> y_double = utils::to_double(y);
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
    polyfit(const arguments &args)
    {
        _args = args;
    }

    void compute(const function &f, const unsigned int &order, const std::string &output_name)
    {
        std::ofstream output_file(_args.output + "/" + output_name + ".csv");
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
};