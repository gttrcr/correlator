#include "function.h"
typedef std::pair<std::string, std::string> SOURCE; // property of the dataset (file name and column index)
typedef std::vector<std::pair<SOURCE, corr_function>> FUNCTIONS;

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
bool get_function(const std::vector<std::vector<std::string>> &s_content, std::vector<corr_function> &fs, const arguments &args)
{
    if (s_content.size() == 0)
        return false;

    domain domain;
    std::vector<codomain> codomains(s_content[0].size() - args.domain_size);
    for (unsigned int i = 0; i < s_content.size(); i++)
    {
        if (s_content[i].size() < 1)
            continue;

        for (unsigned int j = 0; j < s_content[i].size(); j++)
            try
            {
                FDST fdst = std::stod(s_content[i][j]);
                if (j < args.domain_size)
                    domain.push_back(fdst);
                else
                    codomains[j - args.domain_size].push_back(fdst);
            }
            catch (...)
            {
                return false;
            }
    }

    for (unsigned int i = 0; i < codomains.size(); i++)
        fs.push_back(corr_function(domain, codomains[i]));

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

        // cycle on every line
        while (std::getline(file, line))
        {
            utils::ltrim(line);

            if (line.empty())
                continue;

            if (line[0] == '#')
                continue;

            char delimiter = 0;
            if (line.find(',') < line.size())
                delimiter = ',';
            else if (line.find(';') < line.size())
                delimiter = ';';
            else if (line.find(' ') < line.size())
                delimiter = ' ';
            else if (line.find('\t') < line.size())
                delimiter = '\t';
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
            throw correlator_exception(error::error_on_reading_csv);

        std::cout << "\tParsing..." << std::endl;
        std::vector<corr_function> f;
        if (!get_function(s_content, f, args))
            throw correlator_exception(error::error_on_get_function);

        for (unsigned int i = 0; i < f.size(); i++)
            fs.push_back(std::pair<SOURCE, corr_function>(SOURCE(std::filesystem::path(file).stem().string(), axis[i]), f[i]));
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
            std::cerr << "Error in is_directory: " << ec.message();

        if (std::filesystem::is_regular_file(path, ec) &&
            (path.extension() == ".csv" || path.extension() == ".txt"))
        {
            std::string filename = path.string();
            csv_files.push_back(filename);
            std::cout << csv_files.size() << ". Found " << filename << std::endl;
        }

        if (ec)
            std::cerr << "Error in is_regular_file: " << ec.message();
    }
}

int main(int argc, char *argv[])
{
    try
    {
        arguments args = arguments::get_arguments(argc, argv);
        analysis::result::get()->set_arguments(args);

        std::vector<std::string> files;
        get_files(args.input, files);
        analysis::result::get()->set_files(files);

        try
        {
            analysis::work(get_functions(files, args), args);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            analysis::result::get()->set_error(e.what());
        }
        catch (...)
        {
            std::cerr << "Generic error" << std::endl;
            analysis::result::get()->set_error("generic error");
        }

        analysis::result::get()->save(args);
        std::cout << "All done" << std::endl;
    }
    catch (correlator_exception &ce)
    {
        std::cerr << ce.what() << std::endl;
        analysis::result::get()->set_error(ce.what());
    }
}