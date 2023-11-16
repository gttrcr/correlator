#ifndef RELEASE_ENV
#define THREAD_SUPPORT
#endif

#include "function.h"
typedef std::pair<std::string, std::string> SOURCE; // property of the dataset (file name and column index)
typedef std::vector<std::pair<SOURCE, corr_function>> FUNCTIONS;

#include "arguments.h"
#include "analysis/work.h"
#include "cli.h"

#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

// return a function from content
bool get_function(const std::vector<std::vector<std::string>> &s_content, std::vector<corr_function> &fs, const arguments &args)
{
    if (s_content.size() == 0)
        return false;

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

            if (std::find(args.domain_indexes.begin(), args.domain_indexes.end(), j) != args.domain_indexes.end())
                domains[domain_current_index++].push_back(fdst);
            else
                codomains[j - domain_current_index].push_back(fdst);
        }
    }

    for (unsigned int i = 0; i < codomains.size(); i++)
        for (unsigned int j = 0; j < domains.size(); j++)
            fs.push_back(corr_function(domains[j], codomains[i]));

    return true;
}

// read a csv file returning content and the list of axis
bool read_file(const std::string &fname, std::vector<std::vector<std::string>> &s_content, std::vector<std::string> &axis)
{
    s_content.clear();
    axis.clear();

    std::vector<std::string> row;
    std::fstream file(fname, std::ios::in);
    if (file.is_open())
    {
        bool first = true;
        std::string line;
        char delimiter = 0;

        // cycle on every line
        while (std::getline(file, line))
        {
            utils::trim(line);

            if (line.empty())
                continue;

            if (line[0] == '#')
                continue;

            if (first)
            {
                if (line.find(',') < line.size())
                    delimiter = ',';
                else if (line.find(';') < line.size())
                    delimiter = ';';
                else if (line.find(' ') < line.size())
                    delimiter = ' ';
                else if (line.find('\t') < line.size())
                    delimiter = '\t';
                else
                {
                    std::cerr << "Cannot find a valid delimiter" << std::endl;
                    return false;
                }
            }

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

            first = false;
        }

        return true;
    }

    return false;
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
        if (!read_file(file, s_content, axis))
        {
            std::cerr << "Error on reading file " << file << std::endl;
            continue;
        }

        std::cout << "\tParsing..." << std::endl;
        std::vector<corr_function> f;
        if (!get_function(s_content, f, args))
        {
            std::cerr << "Error on getting function for file " << file << std::endl;
            continue;
        }

        unsigned int skip = 0;
        for (unsigned int i = 0; i < f.size(); i++)
        {
            if (std::find(args.domain_indexes.begin(), args.domain_indexes.end(), i) != args.domain_indexes.end())
                skip++;
            fs.push_back(std::pair<SOURCE, corr_function>(SOURCE(std::filesystem::path(file).stem().string(), axis[i + skip]), f[i]));
        }
    }

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
        arguments args = arguments::get_arguments(argc, argv);
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