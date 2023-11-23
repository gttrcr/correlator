#pragma once

#include <iostream>
#include <map>

enum error
{
    OK,
    unable_to_open_file,
    empty_file,
    cannot_find_a_valid_delimiter,
    different_number_of_columns,
    domain_exceded_number_of_columns,
};

std::map<error, std::string> error_desc = {
    {error::OK, "OK"},
    {error::unable_to_open_file, "unable_to_open_file"},
    {error::empty_file, "empty_file"},
    {error::cannot_find_a_valid_delimiter, "cannot_find_a_valid_delimiter"},
    {error::different_number_of_columns, "different_number_of_columns"},
    {error::domain_exceded_number_of_columns, "domain_exceded_number_of_columns"},
};