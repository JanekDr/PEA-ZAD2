#include "RNNAlgorithm.h"
#include <limits>
#include <iostream>

RNNAlgorithm::RNNAlgorithm() : best_cost(-1), execution_time_ms(0) {}

void RNNAlgorithm::explore(int current_node, std::vector<bool>& visited, std::vector<int>& path, 
                           long long current_cost, const std::vector<std::vector<int>>& matrix, int dimension) {
    if (path.size() == (size_t)dimension) {
        // Graf uwzględniający powrót
        long long final_cost = current_cost + matrix[current_node][path[0]]; 
        if (best_cost == -1 || final_cost < best_cost) {
            best_cost = final_cost;
            best_path = path;
        }
        return;
    }

    int min_weight = std::numeric_limits<int>::max();
    for (int i = 0; i < dimension; ++i) {
        if (!visited[i]) {
            if (matrix[current_node][i] < min_weight) {
                min_weight = matrix[current_node][i];
            }
        }
    }

    if (min_weight == std::numeric_limits<int>::max()) return;

    std::vector<int> next_nodes;
    for (int i = 0; i < dimension; ++i) {
        if (!visited[i] && matrix[current_node][i] == min_weight) {
            next_nodes.push_back(i);
        }
    }

    // Branchujemy do poszczegolnych rownie dobrych wariantow (jesli jest 1, idzie linowo)
    for (int next_node : next_nodes) {
        visited[next_node] = true;
        path.push_back(next_node);
        
        explore(next_node, visited, path, current_cost + min_weight, matrix, dimension);
        
        path.pop_back();
        visited[next_node] = false;
    }
}

void RNNAlgorithm::run(const TSPInstance& instance, const ConfigManager& config) {
    Timer timer;
    timer.start();
    
    int dimension = instance.getDimension();
    const auto& matrix = instance.getMatrix();
    best_cost = -1; 
    
    for (int start_node = 0; start_node < dimension; ++start_node) {
        std::vector<bool> visited(dimension, false);
        std::vector<int> path;
        path.reserve(dimension);
        
        visited[start_node] = true;
        path.push_back(start_node);
        
        explore(start_node, visited, path, 0, matrix, dimension);

        if (config.show_progress) {
            displayProgress(start_node + 1, dimension, "RNN", config.show_progress);
        }
    }

    timer.stop();
    execution_time_ms = timer.getElapsedMs();
}

long long RNNAlgorithm::getBestCost() const { return best_cost; }
std::vector<int> RNNAlgorithm::getBestPath() const { return best_path; }
double RNNAlgorithm::getExecutionTimeMs() const { return execution_time_ms; }
