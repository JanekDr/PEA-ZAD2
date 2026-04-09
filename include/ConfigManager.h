#pragma once
#include <string>

class ConfigManager {
public:
    // Plik i rozmiar wejściowy
    std::string tsp_file;
    bool generate_new;
    int generate_size;
    bool generate_symmetric;

    // Ustawienia B&B
    std::string algorithm; // np. BB_BFS, BB_DFS_STACK, BB_DFS_REC, BB_LC, RNN
    bool use_rnn_upper_bound; // Flaga decydująca o obliczaniu pierwszego Bound przez RNN

    // Powtórzenia testu
    int repetitions;
    // Oczekiwana wartosc
    long long optimal_value;

    std::string output_csv;
    bool show_progress;

    ConfigManager(const std::string& filename);
};
