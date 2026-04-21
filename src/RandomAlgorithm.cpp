#include "RandomAlgorithm.h"
#include <random>
#include <algorithm>

RandomAlgorithm::RandomAlgorithm() : best_cost(-1) {}

void RandomAlgorithm::run(const TSPInstance& instance, const ConfigManager& config) {
    int dimension = instance.getDimension();
    std::vector<int> current_path(dimension);
    for (int i = 0; i < dimension; ++i) current_path[i] = i;

    std::random_device rd;
    std::mt19937 g(rd());
    
    best_cost = -1;

    for (int i = 1; i <= config.repetitions; ++i) {
        for (int j = dimension - 1; j > 0; --j) {
            std::uniform_int_distribution<int> dist(0, j);
            int k = dist(g);
            std::swap(current_path[j], current_path[k]);
        }
        long long current_cost = instance.calculatePathCost(current_path);

        if (best_cost == -1 || current_cost < best_cost) {
            best_cost = current_cost;
            best_path = current_path;
        }
        
        if (config.show_progress && (i % 1000 == 0 || i == config.repetitions)) {
            displayProgress(i, config.repetitions, "RAND", config.show_progress);
        }
    }
}

long long RandomAlgorithm::getBestCost() const { return best_cost; }
std::vector<int> RandomAlgorithm::getBestPath() const { return best_path; }
