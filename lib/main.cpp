#include "function.h"
typedef std::vector<std::pair<std::string, corr_function>> FUNCTIONS;

#include "error.h"
#include "arguments.h"
#include "analysis/work.h"
#include "analysis/result.h"
#include "cli.h"

#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>

// return a function from content
bool get_function(const std::vector<std::vector<std::string>> &s_content, corr_function &f, const arguments &args)
{
    if (s_content.size() == 0)
        return false;

    f.clear();
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        if (s_content[i].size() > 1)
        {
            for (unsigned int j = 0; j < s_content[i].size(); j++)
                if (std::stod(s_content[i][j]) == std::numeric_limits<FDST>::infinity())
                    throw correlator_exception(error::nan_or_infinity_number);
        }
        else
            throw correlator_exception(error::the_function_has_dimension_less_than_2);

        f.push_back(PAIR(std::stod(s_content[i][0]), std::stod(s_content[i][args.domain_size + args.codomain_column_index - 1])));
    }

    return true;
}

// read a csv file returning content and the list of axis
bool read_csv(const std::string &fname, std::vector<std::vector<std::string>> &s_content, std::vector<std::string> &axis)
{
    s_content.clear();
    axis.clear();

    std::vector<std::string> row;
    std::fstream file(fname, std::ios::in);
    if (file.is_open())
    {
        bool first = true;
        std::string line;

        // cycle on every line
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            char delimiter = 0;
            if (line.find(',') < line.size())
                delimiter = ',';
            else if (line.find(';') < line.size())
                delimiter = ';';
            else
                throw correlator_exception(error::cannot_find_a_valid_delimiter);

            row.clear();
            std::stringstream str(line);
            std::string word;

            // cycle on every word of every line
            while (std::getline(str, word, delimiter))
            {
                word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
                word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
                word.erase(std::remove(word.begin(), word.end(), '\t'), word.end());

                if (first)
                    axis.push_back(word);
                else
                    row.push_back(word);
            }

            if (!first)
                s_content.push_back(row);

            if (first)
                first = false;
        }

        return true;
    }

    return false;
}

// return all functions from csv filename
FUNCTIONS get_functions(const std::vector<std::string> &const_csv_files, const arguments &args)
{
    std::vector<std::string> csv_files(const_csv_files);
    std::sort(csv_files.begin(), csv_files.end());
    FUNCTIONS fs;
    for (std::string file : csv_files)
    {
        std::cout << "File: " << file << std::endl;
        std::cout << "\tReading..." << std::endl;

        std::vector<std::string> axis;
        std::vector<std::vector<std::string>> s_content;
        if (!read_csv(file, s_content, axis))
            throw correlator_exception(error::error_on_reading_csv);

        std::cout << "\tParsing..." << std::endl;
        corr_function f;
        if (!get_function(s_content, f, args))
            throw correlator_exception(error::error_on_get_function);

        fs.push_back(std::pair(std::filesystem::path(file).stem().string(), f));
    }

    return fs;
}

void axis_duplication(FUNCTIONS &fs, const arguments &args)
{
    // for (int i = 0; i < fs.size(); i++)
    // {
    //     // corr_function f = get_function(get_domain(fs[i].swap))
    // }
}

void correlate_from_files(const std::vector<std::string> &csv_files, const arguments &args)
{
    try
    {
        std::cout << "correlate from files..." << std::endl;
        FUNCTIONS fs = get_functions(csv_files, args);

        std::cout << "axis duplication..." << std::endl;
        axis_duplication(fs, args);

        std::cout << "working..." << std::endl;
        analysis::work(fs, args);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        analysis::result::get()->set_error(e.what());
    }
    catch (...)
    {
        std::cout << "generic error" << std::endl;
        analysis::result::get()->set_error("generic error");
    }
}

// get the list of all csv files inside the folder
std::vector<std::string> get_csv_files(const std::string &path)
{
    std::vector<std::string> csv_files;
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".csv")
        {
            std::string filename = std::filesystem::path(entry.path()).string();
            csv_files.push_back(filename);
            std::cout << "Found " << filename << std::endl;
        }
    }

    analysis::result::get()->set_csv_files(csv_files);
    return csv_files;
}

int main(int argc, char *argv[])
{
    try
    {
        arguments args = arguments::get_arguments(argc, argv);
        analysis::result::get()->set_arguments(args);
        std::vector<std::string> csv_files = get_csv_files(args.input);
        if (csv_files.size() > 0)
            correlate_from_files(csv_files, args);
    }
    catch (correlator_exception &ce)
    {
        std::cout << ce.code() << std::endl;
    }
}