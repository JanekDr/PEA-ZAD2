#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include "ConfigManager.h"
#include "TSPInstance.h"
#include "RNNAlgorithm.h"
#include "BranchAndBound.h"

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/resource.h>
#endif
#include "CsvWriter.h"

void printMemoryUsage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        std::cout << "Szczytowe zuzycie pamieci: " << pmc.PeakWorkingSetSize / 1024 << " KB" << std::endl;
    }
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        std::cout << "Szczytowe zuzycie pamieci: " << usage.ru_maxrss << " KB" << std::endl;
    } else {
        std::cout << "Szczytowe zuzycie pamieci: Blad odczytu" << std::endl;
    }
#endif
}

int main() {
    std::cout << "=== Branch and Bound TSP ===" << std::endl;
    ConfigManager config("config.txt");
    TSPInstance tsp;

    if (config.generate_new) {
        std::cout << "Tryb generatora: Wlaczony" << std::endl;
        tsp.generateRandomAndSave(config.tsp_file, config.generate_size, config.generate_symmetric);
    } else {
        std::cout << "Wczytywanie z pliku: " << config.tsp_file << std::endl;
        tsp.loadFromFile(config.tsp_file);
    }
    
    int dimension = tsp.getDimension();
    std::cout << "Rozmiar instancji: " << dimension << " miast" << std::endl;
    std::cout << "Poczatkowy pobor pamieci (sama macierz): " << tsp.getMemoryUsageMB() << " MB" << std::endl;

    std::cout << "\n--- Badanie algorytmu: " << config.algorithm << " ---" << std::endl;
    std::unique_ptr<IAlgorithm> algo;
    
    if (config.algorithm == "RNN") algo = std::make_unique<RNNAlgorithm>();
    else if (config.algorithm == "BB_BFS" || config.algorithm == "BB_DFS_STACK" || 
             config.algorithm == "BB_DFS_REC" || config.algorithm == "BB_LC") {
        algo = std::make_unique<BranchAndBound>();
    }
    else {
        std::cerr << "Nieznany algorytm w config.txt!" << std::endl; return 1;
    }

    double total_time_ms = 0.0;
    long long overall_best_cost = -1;
    std::vector<int> overall_best_path;

    for (int i = 0; i < config.repetitions; ++i) {
        algo->run(tsp, config);
        
        total_time_ms += algo->getExecutionTimeMs();
        long long current_cost = algo->getBestCost();
        
        if (overall_best_cost == -1 || current_cost < overall_best_cost) {
            overall_best_cost = current_cost;
            overall_best_path = algo->getBestPath();
        }
    }

    double average_time_ms = total_time_ms / config.repetitions;
    
    std::cout << "Najlepszy znaleziony koszt: " << overall_best_cost << std::endl;
    std::cout << "Najlepsza sciezka: ";
    for (size_t i=0; i<overall_best_path.size(); ++i) {
        std::cout << overall_best_path[i] << " ";
    }
    std::cout << overall_best_path[0] << std::endl;
    
    if (config.optimal_value > 0) {
        double error = (static_cast<double>(overall_best_cost - config.optimal_value) / config.optimal_value) * 100.0;
        std::cout << "Blad wzgledny do podanego optimum (" << config.optimal_value << "): " << std::fixed << std::setprecision(2) << error << "%" << std::endl;
    }

    std::cout << "Sredni czas wykonania (" << config.repetitions << " powtorzen): " << average_time_ms << " [ms]" << std::endl;

    printMemoryUsage();
    
    CsvWriter csv(config.output_csv);
    csv.writeHeader();
    csv.writeRow(dimension, config.algorithm, overall_best_cost, average_time_ms); 
    std::cout << "Wynik zapisany do: " << config.output_csv << std::endl;
    
    return 0;
}
