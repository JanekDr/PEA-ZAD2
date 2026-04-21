#include "ConfigManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

ConfigManager::ConfigManager(const std::string& filename) {
    // Domyślne wartości
    tsp_file = "data/matrix_10x10.atsp";
    generate_new = false;
    generate_size = 10;
    generate_symmetric = false;
    algorithm = "BB_LC";
    upper_bound_method = "RNN";
    repetitions = 1;
    optimal_value = -1;
    output_csv = "results/wyniki.csv";
    show_progress = true;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie znaleziono pliku config: " << filename << ". Uzyto wartosci domyslnych." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) continue;

        std::string key = line.substr(0, eq_pos);
        std::string val = line.substr(eq_pos + 1);

        // Usuwanie białych znaków
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        val.erase(0, val.find_first_not_of(" \t\r\n"));
        val.erase(val.find_last_not_of(" \t\r\n") + 1);

        if (key == "TSP_FILE") tsp_file = val;
        else if (key == "GENERATE_NEW") generate_new = (val == "1");
        else if (key == "GENERATE_SIZE") generate_size = std::stoi(val);
        else if (key == "GENERATE_SYMMETRIC") generate_symmetric = (val == "1");
        else if (key == "ALGORITHM") algorithm = val;
        else if (key == "UPPER_BOUND_METHOD") upper_bound_method = val;
        else if (key == "REPETITIONS") repetitions = std::stoi(val);
        else if (key == "OPTIMAL_VALUE") optimal_value = std::stoll(val);
        else if (key == "OUTPUT_CSV") output_csv = val;
        else if (key == "SHOW_PROGRESS") show_progress = (val == "1");
    }
    file.close();
}
