#pragma once

#include "../eigen/Eigen/Dense"
#include "../eigen/Eigen/QR"

#include <fstream>

void polyfit(const std::vector<t_space> &t, const std::vector<t_space> &v, std::vector<long_t_space> &coeff, const unsigned int &order)
{
    // Create Matrix Placeholder of size n x k, n= number of datapoints, k = order of polynomial, for exame k = 3 for cubic polynomial
    Eigen::MatrixXd T(t.size(), order + 1);
    Eigen::VectorXd V = Eigen::VectorXd::Map(&v.front(), v.size());
    Eigen::VectorXd result;

    // check to make sure inputs are correct
    assert(t.size() == v.size());
    assert(t.size() >= order + 1);
    
    // Populate the matrix
    for (size_t i = 0; i < t.size(); ++i)
        for (size_t j = 0; j < order + 1; ++j)
            T(i, j) = pow(t.at(i), j);

    // Solve for linear least square fit
    result = T.householderQr().solve(V);
    coeff.resize(order + 1);
    for (unsigned int k = 0; k < order + 1; k++)
        coeff[k] = result[k];
}

template <unsigned int domain_size, unsigned int codomain_size>
std::vector<long_t_space> polyfit(const function<domain_size, codomain_size> &f1, const function<domain_size, codomain_size> &f2, const unsigned int &order)
{
    std::vector<t_space> x;
    for (unsigned int i = 0; i < f1.size(); i++)
        x.push_back(f1.get(i, 1));

    std::vector<t_space> y;
    for (unsigned int i = 0; i < f2.size(); i++)
        y.push_back(f2.get(i, 1));

    std::vector<long_t_space> c;
    polyfit(x, y, c, order);

    return c;
}

template <unsigned int domain_size, unsigned int codomain_size>
void polyfit(const std::vector<std::tuple<std::string, function<domain_size, codomain_size>>> &fs, const unsigned int &order)
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
                std::vector<long_t_space> c = polyfit(std::get<1>(fs[i]), std::get<1>(fs[j]), ord);
                output_file << ord << "," << i << "," << j << ",";
                for (unsigned int o = 0; o < c.size(); o++)
                    output_file << c[o] << ",";
                output_file << std::endl;
            }
        }
    }

    output_file.close();
}