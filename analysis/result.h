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
            _result["args"]["codomain_column_index"] = args.codomain_column_index;
            _result["args"][""] = args.domain_size;
            _result["args"]["input"] = args.input;
            _result["args"]["number_of_fft_peaks_to_compute"] = args.number_of_fft_peaks_to_compute;
            _result["args"]["output"] = args.output;
        }

        void save()
        {
            std::ofstream o("result.json");
            o << _result << std::endl;
            o.close();
        }
    };
}