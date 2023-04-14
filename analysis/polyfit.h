#pragma once

#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include <fstream>

class polyfit
{
private:
    static void _polyfit(const std::vector<default_type> &x, const std::vector<default_type> &y, std::vector<default_type> &coeff, const unsigned int &order)
    {
        // Create Matrix Placeholder of size n x k, n= number of datapoints, k = order of polynomial, for exame k = 3 for cubic polynomial
        Eigen::MatrixXd T(x.size(), order + 1);
        Eigen::VectorXd V = Eigen::VectorXd::Map(&y.front(), y.size());
        Eigen::VectorXd result;

        // check to make sure inputs are correct
        assert(x.size() == y.size());
        assert(x.size() >= order + 1);

        // Populate the matrix
        for (size_t i = 0; i < x.size(); ++i)
            for (size_t j = 0; j < order + 1; ++j)
                T(i, j) = pow(x.at(i), j);

        // Solve for linear least square fit
        result = T.householderQr().solve(V);
        coeff.resize(order + 1);
        for (unsigned int k = 0; k < order + 1; k++)
            coeff[k] = result[k];
    }

public:
    template <unsigned int domain_size, unsigned int codomain_size>
    static void pf(const function<default_type, domain_size, codomain_size> &f, const unsigned int &order)
    {
        std::vector<default_type> x;
        std::vector<default_type> y;
        for (unsigned int i = 0; i < f.size(); i++)
        {
            x.push_back(f.get_domain(i).val());
            y.push_back(std::log(f.get_codomain(i).val()));
        }

        std::ofstream output_file("output/peaks_migration.csv");
        output_file << "degree,";
        for (unsigned int i = 0; i < order; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;

        for (unsigned int ord = 0; ord < order; ord++)
        {
            std::vector<default_type> c;
            _polyfit(x, y, c, ord);
            output_file << ord << ",";
            for (unsigned int o = 0; o < c.size(); o++)
                output_file << c[o] << ",";
            output_file << std::endl;
        }

        output_file.close();
    }

    template <unsigned int domain_size, unsigned int codomain_size>
    static void pf(const std::vector<std::tuple<std::string, function<default_type, domain_size, codomain_size>>> &fs, const unsigned int &order)
    {
        std::ofstream output_file("output/polynomial_fit.csv");
        output_file << "degree,f1,f2,";
        for (unsigned int i = 0; i < order; i++)
            output_file << "b" << i << ",";
        output_file << std::endl;

        for (unsigned int ord = 0; ord < order; ord++)
        {
            for (unsigned int i = 0; i < fs.size(); i++)
            {
                for (unsigned int j = i + 1; j < fs.size(); j++)
                {
                    function<default_type, domain_size, codomain_size> f;
                    std::vector<default_type> x;
                    std::vector<default_type> y;
                    for (unsigned int k = 0; k < std::get<1>(fs[i]).size(); k++)
                    {
                        x.push_back(std::get<1>(fs[i]).get_domain(k).val());
                        y.push_back(std::get<1>(fs[j]).get_codomain(k).val());
                    }

                    std::vector<default_type> c;
                    _polyfit(x, y, c, ord);
                    output_file << ord << "," << i << "," << j << ",";
                    for (unsigned int o = 0; o < c.size(); o++)
                        output_file << c[o] << ",";
                    output_file << std::endl;
                }
            }
        }

        output_file.close();
    }
};