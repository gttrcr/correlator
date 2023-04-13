#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <cmath>
#include <algorithm>

#define t_space double
#define long_t_space long t_space

template <unsigned int size>
class vec
{
private:
    long_t_space _v[size];

public:
    vec()
    {
        for (unsigned int i = 0; i < size; i++)
            _v[i] = 0;
    }

    vec(const vec<size> &v)
    {
        for (unsigned int i = 0; i < size; i++)
            _v[i] = v.get(i);
    }

    vec(const long_t_space &v)
    {
        _v[0] = v;
    }

    void set(const unsigned int &pos, const long_t_space &value)
    {
        _v[pos] = value;
    }

    long_t_space get(const unsigned int &pos) const
    {
        return _v[pos];
    }

    vec<size> pow(const long_t_space &d) const
    {
        vec<size> v;
        for (unsigned int i = 0; i < size; i++)
            v.set(i, std::pow(_v[i], d));
        return v;
    }

    vec<size> log() const
    {
        vec<size> v;
        for (unsigned int i = 0; i < size; i++)
            v.set(i, std::log(_v[i]));
        return v;
    }

    vec<1> norm(const long_t_space p = 1) const
    {
        long_t_space sum = 0;
        for (unsigned int i = 0; i < size; i++)
            sum += std::pow(std::fabs(_v[i]), p);
        return vec<1>(std::pow(sum, 1 / p));
    }

    inline bool operator<(const vec<1> &rhs)
    {
        return _v[0] < rhs._v[0];
    }
};

// template <unsigned int size_1, unsigned int size_2>

// template <unsigned int size_1, unsigned int size_2>
// inline bool operator>(const vec<size_1> &lhs, const vec<size_2> &rhs)
//{
//     return rhs < lhs;
// }

template <unsigned int size>
class domain : public vec<size>
{
public:
    domain() = default;

    domain(const vec<size> &v) : vec<size>(v) {}
};

template <unsigned int size>
class codomain : public vec<size>
{
public:
    codomain() = default;

    codomain(const vec<size> &v) : vec<size>(v) {}
};

template <unsigned int domain_size, unsigned int codomain_size>
class function
{
private:
    std::vector<std::tuple<domain<domain_size>, codomain<codomain_size>>> _f;

public:
    void set(const domain<domain_size> &d, const codomain<codomain_size> &c)
    {
        _f.push_back(std::make_tuple(d, c));
    }

    void clear()
    {
        _f.clear();
    }

    long_t_space get(const unsigned int &pos, const unsigned int &variable_position) const
    {
        if (variable_position < domain_size)
            return std::get<0>(_f[pos]).get(variable_position);
        else
            return std::get<1>(_f[pos]).get(variable_position - domain_size);
    }

    unsigned int size() const
    {
        return _f.size();
    }

    function<domain_size, codomain_size> pow(const long_t_space p) const
    {
        function<domain_size, codomain_size> f;
        for (unsigned int i = 0; i < _f.size(); i++)
            f.set(std::get<0>(_f[i]), std::get<1>(_f[i]).pow(p));

        return f;
    }

    function<domain_size, codomain_size> log() const
    {
        function<domain_size, codomain_size> f;
        for (unsigned int i = 0; i < _f.size(); i++)
            f.set(std::get<0>(_f[i]), std::get<1>(_f[i]).log());

        return f;
    }

    function<domain_size, 1> norm(const long_t_space &p) const
    {
        function<domain_size, 1> f;
        for (unsigned int i = 0; i < _f.size(); i++)
            f.set(std::get<0>(_f[i]), std::get<1>(_f[i]).norm(p));

        return f;
    }

    function<domain_size, codomain_size> maximas(const unsigned int &number_of_peaks)
    {
        std::vector<std::tuple<domain<domain_size>, codomain<codomain_size>>> cp(_f);

        // sort descending
        std::sort(cp.begin(), cp.end(), [](const std::tuple<domain<domain_size>, codomain<codomain_size>> &lhs, const std::tuple<domain<domain_size>, codomain<codomain_size>> &rhs)
                  { return std::get<1>(rhs).norm(2) < std::get<1>(lhs).norm(2); });

        function<domain_size, codomain_size> ret;
        for (unsigned int i = 0; i < number_of_peaks; i++)
            ret.set(std::get<0>(cp[i]), std::get<1>(cp[i]));

        return ret;
    }
};