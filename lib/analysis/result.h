#pragma once

#include "../json.hpp"
#include "../arguments.h"
using json = nlohmann::json;

#include <fstream>

namespace analysis
{
    class metadata
    {
    private:
        json _result;
        static metadata *_instance;
        metadata()
        {
            _result.clear();
        }

    public:
        static metadata *get()
        {
            if (metadata::_instance == nullptr)
                metadata::_instance = new metadata();

            return metadata::_instance;
        }

        void set_arguments(const arguments &args)
        {
            _result["args"]["input"] = args.input;
            _result["args"]["output"] = args.output;
            _result["args"]["fft_peaks_to_compute"] = args.fft_peaks_to_compute;
            _result["args"]["domain_indexes"] = args.domain_indexes;
            _result["args"]["polyfit_max_degree"] = args.polyfit_max_degree;
        }

        void set_files(const std::vector<std::string> &csv_files)
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
            bool found = false;
            for (unsigned int i = 0; i < _result["analysis"].size(); i++)
            {
                if (_result["analysis"][i].is_null())
                    continue;

                if (!_result["analysis"][i].contains("work"))
                    continue;

                std::string work = _result["analysis"][i]["work"];
                if (node == work)
                {
                    _result["analysis"][i]["output"].push_back(subnode);
                    found = true;
                }
            }

            if (!found)
            {
                unsigned int size = _result["analysis"].size();
                _result["analysis"][size]["work"] = node;
                _result["analysis"][size]["output"].push_back(subnode);
            }
        }

        void save(const arguments &args)
        {
            std::ofstream o(args.output + "/metadata.json");
            o << _result << std::endl;
            o.close();
        }
    };
}

analysis::metadata *analysis::metadata::_instance = 0;