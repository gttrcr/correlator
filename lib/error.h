#pragma once

#include <iostream>

enum error
{
    OK = 0,
    cannot_find_a_valid_delimiter,
    nan_or_infinity_number,
    the_function_has_dimension_less_than_2,
    error_on_reading_csv,
    error_on_get_function,
    cannot_create_output_directory
};

class correlator_exception : public std::exception
{
private:
    const error _err;

public:
    correlator_exception(error err) : _err(err) {}

    error err() const
    {
        return _err;
    }

    const char *what() const noexcept override
    {
        return std::to_string(_err).c_str();
    }
};