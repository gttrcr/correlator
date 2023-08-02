#pragma once

#include "../function.h"
#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include "../statistics.h"
#include "../utils.h"

#include <fstream>
#include <map>
#include <filesystem>
#include <algorithm>

class polyfit
{
private:
    struct data
    {
    public:
        unsigned int degree;
        FDST r2;
        std::string name;
        CODOMAIN coeff;
    };

    arguments _args;
    std::vector<data> _data;

    // // std::vector<FDST> a = {0, 2, 0, 3, 5};
    // // std::vector<FDST> b = {7, 11, 0};
    // // std::vector<FDST> p = compute::poly_product(a, b);
    // static std::vector<FDST> _poly_product(const std::vector<FDST> &a, const std::vector<FDST> &b)
    // {
    //     std::vector<FDST> coeff(std::max(a.size(), b.size()) + 1);
    //     for (unsigned int i = 0; i < a.size(); i++)
    //         for (unsigned int j = 0; j < b.size(); j++)
    //             coeff[i + j] += a[i] * b[j];

    //     return coeff;
    // }

    void _polyfit(const DOMAIN &x, const CODOMAIN &y, CODOMAIN &coeff, const unsigned int &degree)
    {
        std::vector<double> y_double = utils::to_double(y);
        Eigen::MatrixXd T(x.size(), degree + 1);
        Eigen::VectorXd V = Eigen::VectorXd::Map(&y_double.front(), y_double.size());
        Eigen::VectorXd result;

        assert(x.size() == y.size());
        assert(x.size() >= degree + 1);

        for (size_t i = 0; i < x.size(); ++i)
            for (size_t j = 0; j < degree + 1; ++j)
                T(i, j) = pow(x.at(i), j);

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

    void compute(const corr_function &f, const unsigned int &degree, const std::string &name)
    {
        for (unsigned int deg = 0; deg <= degree; deg++)
        {
            DOMAIN x = f.get_domain();
            CODOMAIN y = f.get_codomain();
            CODOMAIN c;
            _polyfit(x, y, c, deg);
            FDST r2 = statistics::get_r2(x, y, c);
            _data.push_back({deg, r2, name, c});
        }
    }

    // save all computed correlation and clear all _data
    void save(const std::string &output_folder, const std::string &output_file)
    {
        // order by r2 descending and then by degree ascending
        std::sort(_data.begin(), _data.end(), [](const data &d1, const data &d2)
                  {
                      return std::tie(d2.r2, d1.degree) < std::tie(d1.r2, d2.degree);
                      // if(d1.r2 != d2.r2)
                      //    return d1.r2 > d2.r2;
                      // return d1.degree < d2.degree;
                  });

        std::filesystem::create_directory(_args.output + "/" + output_folder);
        std::ofstream of(_args.output + "/" + output_folder + "/" + output_file);
        of << "degree,r^2,file,";

        // get the heighest degree in da
        unsigned int degree = std::max_element(_data.begin(), _data.end(), [](const data &d1, const data &d2)
                                               { return d1.degree < d2.degree; })
                                  ->degree;
        for (unsigned int i = 0; i <= degree; i++)
            of << "d" << i << ",";
        of << std::endl;

        for (unsigned int i = 0; i < _data.size(); i++)
        {
            of << _data[i].degree << "," << _data[i].r2 << "," << _data[i].name << ",";
            for (unsigned int j = 0; j < _data[i].coeff.size(); j++)
                of << _data[i].coeff[j] << ",";
            of << std::endl;
        }

        _data.clear();
        of.close();
    }
};