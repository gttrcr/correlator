#ifndef RELEASE_ENV
#define THREAD_SUPPORT
#endif

#include "function.h"

struct source
{
public:
    std::string filename;
    std::string domain_axis;
    std::string codomain_axis;
};
typedef struct source SOURCE;

struct FUNCTION
{
public:
    SOURCE source;
    corr_function function;
};
typedef std::vector<FUNCTION> FUNCTIONS;

#include "error.h"
#include "arguments.h"
#include "analysis/work.h"
#include "cli.h"

#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

// return a function from content
error get_function(const std::vector<std::vector<std::string>> &s_content, std::vector<corr_function> &fs, const arguments &args)
{
    if (s_content.size() == 0)
        return error::empty_file;

    const unsigned int line_size = s_content[0].size();
    if (!std::all_of(s_content.begin(), s_content.end(), [line_size](const std::vector<std::string> content)
                     { return content.size() == line_size; }))
        return error::different_number_of_columns;

    const unsigned int max_domain_indices = *std::max_element(args.domain_indexes.begin(), args.domain_indexes.end());
    if (line_size <= max_domain_indices)
        return error::domain_exceded_number_of_columns;

    std::vector<domain> domains(args.domain_indexes.size());
    std::vector<codomain> codomains(s_content[0].size() - args.domain_indexes.size());
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        if (s_content[i].size() < 1)
            continue;

        unsigned int domain_current_index = 0;
        for (unsigned int j = 0; j < s_content[i].size(); j++)
        {
            FDST fdst = std::numeric_limits<double>::quiet_NaN();
            if (utils::is_number(s_content[i][j]))
                fdst = std::stod(s_content[i][j]);
            else
            {
                std::string trimmed_s_content(s_content[i][j]);
                utils::trim(trimmed_s_content);
                if (utils::is_number(trimmed_s_content))
                    fdst = std::stod(trimmed_s_content);
            }

            if (std::find(args.domain_indexes.begin(), args.domain_indexes.end(), j) != args.domain_indexes.end())
                domains[domain_current_index++].push_back(fdst);
            else
                codomains[j - domain_current_index].push_back(fdst);
        }
    }

    for (unsigned int i = 0; i < codomains.size(); i++)
        for (unsigned int j = 0; j < domains.size(); j++)
            fs.push_back(corr_function(domains[j], codomains[i]));

    return error::OK;
}

// read a csv file returning content and the list of axis
const std::string delimiters = ",\t; \r\n";
error read_file(const std::string &fname, std::vector<std::vector<std::string>> &s_content, std::vector<std::string> &axis)
{
    s_content.clear();
    axis.clear();

    std::fstream file(fname, std::ios::in);
    if (file.is_open())
    {
        bool first = true;
        std::string line;
        char delimiter = 0;

        // cycle on every line
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::string trimmed_line(line);
            utils::trim(trimmed_line);
            if (trimmed_line.empty() || trimmed_line[0] == '#')
                continue;

            if (first)
            {
                bool found = false;
                for (unsigned int i = 0; i < delimiters.size() && !found; i++)
                    if ((found = (line.find(delimiters[i]) < line.size())))
                        delimiter = delimiters[i];

                if (!found)
                    return error::cannot_find_a_valid_delimiter;
            }

            std::string word;
            std::stringstream str(line);
            std::vector<std::string> row;
            // cycle on every word of every line
            while (std::getline(str, word, delimiter))
            {
                word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());

                if (first)
                    axis.push_back(word);
                else
                    row.push_back(word);
            }

            if (!first)
            {
                for (unsigned int i = row.size(); i <= axis.size(); i++)
                    row.push_back("");
                s_content.push_back(row);
            }

            first = false;
        }

        return error::OK;
    }

    return error::unable_to_open_file;
}

// return all functions from csv filename
FUNCTIONS get_functions(const std::vector<std::string> &files, const arguments &args)
{
    std::cout << "Get functions..." << std::endl;

    FUNCTIONS fs;
    for (std::string file : files)
    {
        std::cout << "\tFile: " << file << std::endl;
        std::cout << "\t\tReading..." << std::endl;

        std::vector<std::string> axis;
        std::vector<std::vector<std::string>> s_content;
        error err = read_file(file, s_content, axis);
        if (err != error::OK)
        {
            std::cerr << "Error on reading file " << error_desc[err] << std::endl;
            continue;
        }

        std::cout << "\t\tParsing..." << std::endl;
        std::vector<corr_function> f;
        err = get_function(s_content, f, args);
        if (err != error::OK)
        {
            std::cerr << "\t\tError on getting function: " << error_desc[err] << std::endl;
            continue;
        }

        std::vector<std::string> domain_axis;
        std::vector<std::string> codomain_axis;
        for (unsigned int i = 0; i < axis.size(); i++)
        {
            if (std::find(args.domain_indexes.begin(), args.domain_indexes.end(), i) != args.domain_indexes.end())
                domain_axis.push_back(axis[i]);
            else
                codomain_axis.push_back(axis[i]);
        }

        for (unsigned int i = 0; i < codomain_axis.size(); i++)
        {
            std::string codomain_axis_name = codomain_axis[i];
            for (unsigned int j = 0; j < domain_axis.size(); j++)
            {
                std::string domain_axis_name = domain_axis[j];
                fs.push_back((FUNCTION){(SOURCE){std::filesystem::path(file).stem().string(), domain_axis_name, codomain_axis_name}, f[i * domain_axis.size() + j]});
            }
        }
    }

    // if (args.merge)
    //     for (unsigned int i = 0; i < fs.size(); i++)
    //     {
    //         std::cout << "a" << std::endl;
    //     }

    return fs;
}

// get the list of all csv files inside the folder
void get_files(const std::vector<std::string> &path_str_vector, std::vector<std::string> &csv_files)
{
    for (unsigned int i = 0; i < path_str_vector.size(); i++)
    {
        std::string path_str = path_str_vector[i];
        const std::filesystem::path path(path_str);
        std::error_code ec;
        if (std::filesystem::is_directory(path, ec))
            for (const auto &entry : std::filesystem::directory_iterator(path))
                get_files({entry.path().string()}, csv_files);

        if (ec)
            std::cerr << "Error in is_directory: " << ec.message() << std::endl;

        if (std::filesystem::is_regular_file(path, ec) &&
            (path.extension() == ".csv" || path.extension() == ".txt"))
        {
            std::string filename = path.string();
            csv_files.push_back(filename);
            std::cout << csv_files.size() << ". Found " << filename << std::endl;
        }

        if (ec)
            std::cerr << "Error in is_regular_file: " << ec.message() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    try
    {
        arguments args;
        if (arguments::get_arguments(argc, argv, args))
        {
            analysis::metadata::get()->set_arguments(args);

            std::vector<std::string> files;
            get_files(args.input, files);
            analysis::metadata::get()->set_files(files);

            try
            {
                FUNCTIONS fs = get_functions(files, args);
                analysis::work(fs, args);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Exception during work " << e.what() << std::endl;
                analysis::metadata::get()->set_error("Exception during work " + std::string(e.what()));
                return -1;
            }
            catch (...)
            {
                std::cerr << "Generic error during work" << std::endl;
                analysis::metadata::get()->set_error("Generic error during work");
                return -1;
            }

            analysis::metadata::get()->save(args);
            std::cout << "All done" << std::endl;

            return 0;
        }

        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
        analysis::metadata::get()->set_error("Exception " + std::string(e.what()));
        return -1;
    }
    catch (...)
    {
        std::cerr << "Generic error" << std::endl;
        analysis::metadata::get()->set_error("generic error");
        return -1;
    }
}