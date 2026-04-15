#pragma once
#include "IAlgorithm.h"

class RNNAlgorithm : public IAlgorithm {
private:
    long long best_cost;
    std::vector<int> best_path;

    void explore(int current_node, std::vector<bool>& visited, std::vector<int>& path, 
                 long long current_cost, const std::vector<std::vector<int>>& matrix, int dimension);

public:
    RNNAlgorithm();
    void run(const TSPInstance& instance, const ConfigManager& config) override;
    long long getBestCost() const override;
    std::vector<int> getBestPath() const override;
};
