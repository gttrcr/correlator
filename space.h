#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <cmath>
#include <algorithm>

// #define default_type double
// #define default_type long default_type

template <typename T, unsigned int size>
class vec
{
private:
    T _v[size];

public:
    vec()
    {
        for (unsigned int i = 0; i < size; i++)
            _v[i] = 0;
    }

    vec(const vec<T, size> &v)
    {
        for (unsigned int i = 0; i < size; i++)
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

    T norm(const double p = 2) const
    {
        T sum = 0;
        for (unsigned int i = 0; i < size; i++)
            sum += std::pow(std::fabs(_v[i]), p);
        return std::pow(sum, 1 / p);
    }

    vec<T, size> operator-(const vec<T, size> &v) const
    {
        vec<T, size> ret_v;
        for (unsigned int i = 0; i < size; i++)
            ret_v.set(i, _v[i] - v._v[i]);

        return ret_v;
    }

    // TODO remove this function and use the multidimensional analysis
    T val() const
    {
        if (size == 1)
            return _v[0];
        throw std::runtime_error("non scalar type");
    }
};

template <typename T, unsigned int size>
class domain : public vec<T, size>
{
public:
    domain() = default;

    domain(const vec<T, size> &v) : vec<T, size>(v) {}
};

template <typename T, unsigned int size>
class codomain : public vec<T, size>
{
public:
    codomain() = default;

    codomain(const vec<T, size> &v) : vec<T, size>(v) {}
};

template <typename T, unsigned int domain_size, unsigned int codomain_size>
class function
{
private:
    std::vector<std::tuple<domain<T, domain_size>, codomain<T, codomain_size>>> _f;

public:
    void set(const domain<T, domain_size> &d, const codomain<T, codomain_size> &c)
    {
        _f.push_back(std::make_tuple(d, c));
    }

    void clear()
    {
        _f.clear();
    }

    domain<T, domain_size> get_domain(const unsigned int &pos) const
    {
        return std::get<0>(_f[pos]);
    }

    codomain<T, codomain_size> get_codomain(const unsigned int &pos) const
    {
        return std::get<1>(_f[pos]);
    }

    unsigned int size() const
    {
        return _f.size();
    }

    function<T, domain_size, 1> norm(const double &p) const
    {
        function<default_type, domain_size, 1> f;
        for (unsigned int i = 0; i < _f.size(); i++)
            f.set(std::get<0>(_f[i]), std::get<1>(_f[i]).norm(p));

        return f;
    }

    function<T, domain_size, codomain_size> maximas(const unsigned int &number_of_peaks)
    {
        std::vector<std::tuple<domain<T, domain_size>, codomain<T, codomain_size>>> cp(_f);

        // sort descending
        std::sort(cp.begin(), cp.end(), [](const std::tuple<domain<T, domain_size>, codomain<T, codomain_size>> &lhs, const std::tuple<domain<default_type, domain_size>, codomain<default_type, codomain_size>> &rhs)
                  { return std::get<1>(rhs).norm() < std::get<1>(lhs).norm(); });

        function<T, domain_size, codomain_size> ret;
        for (unsigned int i = 0; i < number_of_peaks; i++)
            ret.set(std::get<0>(cp[i]), std::get<1>(cp[i]));

        return ret;
    }
};