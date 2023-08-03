#pragma once

#include "../json.hpp"
#include "../arguments.h"
using json = nlohmann::json;

#include <fstream>

namespace analysis
{
    class result
    {
    private:
        json _result;
        static result *_instance;
        result()
        {
            _result.clear();
        }

    public:
        static result *get()
        {
            if (result::_instance == nullptr)
                result::_instance = new result();

            return result::_instance;
        }

        void set_arguments(const arguments &args)
        {
            _result["args"]["input"] = args.input;
            _result["args"]["output"] = args.output;
            _result["args"]["number_of_fft_peaks_to_compute"] = args.number_of_fft_peaks_to_compute;
            _result["args"]["domain_size"] = args.domain_size;
            _result["args"]["polyfit_max_degree"] = args.polyfit_max_degree;
        }

        void set_csv_files(const std::vector<std::string> &csv_files)
        {
            for (unsigned int i = 0; i < csv_files.size(); i++)
                _result["csv_files"].push_back(csv_files[i]);
        }

        void set_error(const std::string &err)
        {
            _result["error"].push_back(err);
        }

        void set_analysis(const std::string &node, const std::string &subnode)
        {
            if (_result["analysis"].size() == 0)
            {
                _result["analysis"][0]["work"] = node;
                _result["analysis"][0]["output"].push_back(subnode);
            }
            else
            {
                bool found = false;
                for (unsigned int i = 0; i < _result["analysis"].size(); i++)
                {
                    std::string work = _result["analysis"][i]["work"];
                    if (node == work)
                    {
                        _result["analysis"][i]["output"].push_back(subnode);
                        found = true;
                    }
                }

                if (!found)
                {
                    _result["analysis"][_result["analysis"].size()]["work"] = node;
                    _result["analysis"][_result["analysis"].size()]["output"].push_back(subnode);
                }
            }
        }

        void save(const arguments &args)
        {
            std::ofstream o(args.output + "/result.json");
            o << _result << std::endl;
            o.close();
        }
    };
}

analysis::result *analysis::result::_instance = 0;