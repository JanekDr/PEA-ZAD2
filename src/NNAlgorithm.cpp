#include "NNAlgorithm.h"
#include <limits>
#include <iostream>

NNAlgorithm::NNAlgorithm() : best_cost(-1) {}

void NNAlgorithm::run(const TSPInstance& instance, const ConfigManager& config) {
    int dimension = instance.getDimension();
    const auto& matrix = instance.getMatrix();
    
    std::vector<int> current_path;
    current_path.reserve(dimension);
    std::vector<bool> visited(dimension, false);
    
    int current_node = 0;
    current_path.push_back(current_node);
    visited[current_node] = true;
    long long current_cost = 0;

    for (int step = 1; step < dimension; ++step) {
        int best_next = -1;
        int min_weight = std::numeric_limits<int>::max();

        for (int i = 0; i < dimension; ++i) {
            if (!visited[i]) {
                if (matrix[current_node][i] < min_weight) {
                    min_weight = matrix[current_node][i];
                    best_next = i;
                }
            }
        }

        visited[best_next] = true;
        current_path.push_back(best_next);
        current_cost += min_weight;
        current_node = best_next;

        displayProgress(step, dimension - 1, "NN", config.show_progress);
    }

    current_cost += matrix[current_node][current_path[0]];
    
    best_cost = current_cost;
    best_path = current_path;
}

long long NNAlgorithm::getBestCost() const { return best_cost; }
std::vector<int> NNAlgorithm::getBestPath() const { return best_path; }
