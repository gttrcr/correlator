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
        cdt r2;
        std::string name;
        codomain coeff;
    };

    arguments _args;
    std::vector<data> _data;

    void _polyfit(const domain &x, const codomain &y, codomain &coeff, const unsigned int &degree)
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

    void compute(const function &f, const unsigned int &degree, const std::string &name)
    {
        for (unsigned int deg = 0; deg < degree; deg++)
        {
            domain x = get_domain(f);
            codomain y = get_codomain(f);
            codomain c;
            _polyfit(x, y, c, deg);
            cdt r2 = statistics::get_r2(x, y, c);
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
        std::ofstream of(_args.output + "/" + output_folder + "/" + output_file + ".csv");
        of << "degree,r^2,file,";

        // get the heighest degree in da
        unsigned int degree = std::max_element(_data.begin(), _data.end(), [](const data &d1, const data &d2)
                                               { return d1.degree < d2.degree; })
                                  ->degree;
        for (unsigned int i = 0; i <= degree; i++)
            of << "b" << i << ",";
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