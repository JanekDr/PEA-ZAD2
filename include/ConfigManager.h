#pragma once
#include <string>

class ConfigManager {
public:
    std::string tsp_file;
    bool generate_new;
    int generate_size;
    bool generate_symmetric;

    std::string algorithm;
    bool use_rnn_upper_bound;

    int repetitions;
    long long optimal_value;

    std::string output_csv;
    bool show_progress;

    ConfigManager(const std::string& filename);
};
