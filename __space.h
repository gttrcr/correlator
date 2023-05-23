/*
#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <cmath>
#include <algorithm>

template <unsigned int dim = 1, typename T = default_type>
class vec
{
private:
    T _v[dim];

public:
    vec()
    {
        for (unsigned int i = 0; i < dim; i++)
            _v[i] = 0;
    }

    vec(const vec<dim, T> &v)
    {
        for (unsigned int i = 0; i < dim; i++)
            _v[i] = v.get(i);
    }

    vec(const T &v)
    {
        _v[0] = v;
    }

    void set(const unsigned int &pos, const T &value)
    {
        _v[pos] = value;
    }

    T get(const unsigned int &pos) const
    {
        return _v[pos];
    }

    unsigned int size() const
    {
        return dim;
    }

    T norm(const double p = 2) const
    {
        T sum = 0;
        for (unsigned int i = 0; i < dim; i++)
            sum += std::pow(std::fabs(_v[i]), p);
        return std::pow(sum, 1 / p);
    }

    vec<dim, T> operator-(const vec<dim, T> &v) const
    {
        vec<dim, T> ret_v;
        for (unsigned int i = 0; i < dim; i++)
            ret_v.set(i, _v[i] - v._v[i]);

        return ret_v;
    }
};

template <unsigned int dim = 1, typename T = default_type>
class domain : public vec<dim, T>
{
public:
    domain() = default;

    domain(const vec<dim, T> &v) : vec<dim, T>(v) {}
};

template <unsigned int dim = 1, typename T = default_type>
class codomain : public vec<dim, T>
{
public:
    codomain() = default;

    codomain(const vec<dim, T> &v) : vec<dim, T>(v) {}
};

template <unsigned int domain_dim = 1, unsigned int codomain_dim = 1, typename T = default_type>
class function
{
private:
    std::vector<std::tuple<domain<domain_dim, T>, codomain<codomain_dim, T>>> _f;

public:
    void set(const domain<domain_dim, T> &d, const codomain<codomain_dim, T> &c)
    {
        _f.push_back(std::make_tuple(d, c));
    }

    void clear()
    {
        _f.clear();
    }

    domain<domain_dim, T> get_domain(const unsigned int &pos) const
    {
        return std::get<0>(_f[pos]);
    }

    codomain<codomain_dim, T> get_codomain(const unsigned int &pos) const
    {
        return std::get<1>(_f[pos]);
    }

    unsigned int size() const
    {
        return _f.size();
    }

    function<domain_dim, 1, T> norm(const double &p) const
    {
        function<domain_dim, 1> f;
        for (unsigned int i = 0; i < _f.dim(); i++)
            f.set(std::get<0>(_f[i]), std::get(_f[i]).norm(p));

        return f;
    }

    function<domain_dim, codomain_dim, T> maximas(const unsigned int &number_of_peaks)
    {
        std::vector<std::tuple<domain<domain_dim, T>, codomain<codomain_dim, T>>> cp(_f);

        // sort descending
        std::sort(cp.begin(), cp.end(), [](const std::tuple<domain<domain_dim, T>, codomain<codomain_dim, T>> &lhs, const std::tuple<domain<domain_dim>, codomain<codomain_dim>> &rhs)
                  { return std::get(rhs).norm() < std::get(lhs).norm(); });

        function<domain_dim, codomain_dim, T> ret;
        for (unsigned int i = 0; i < number_of_peaks; i++)
            ret.set(std::get<0>(cp[i]), std::get(cp[i]));

        return ret;
    }
};
*/