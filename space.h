#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <math.h>
#include <functional>

#define t_space double

template <unsigned int size>
class vec
{
private:
    t_space _v[size];

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

    vec(const t_space &v)
    {
        _v[0] = v;
    }

    void set(const unsigned int &pos, const t_space &value)
    {
        _v[pos] = value;
    }

    t_space get(const unsigned int &pos) const
    {
        return _v[pos];
    }

    vec<size> pow(const t_space &d) const
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

    vec<1> norm(const t_space p = 1) const
    {
        t_space sum = 0;
        for (unsigned int i = 0; i < size; i++)
            sum += pow(abs(_v[i]), p);
        return vec<1>(pow(sum, 1 / p));
    }
};

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

    t_space get(const unsigned int &pos, const unsigned int &variable_position) const
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

    function<domain_size, codomain_size> pow(const t_space p) const
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

    function<domain_size, 1> norm(const t_space &p) const
    {
        function<domain_size, 1> f;
        for (unsigned int i = 0; i < _f.size(); i++)
            f.set(std::get<0>(std::get<0>(_f[i]), std::get<1>(_f[i]).norm(p)));

        return f;
    }
};