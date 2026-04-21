#pragma once
#include "IAlgorithm.h"

class RandomAlgorithm : public IAlgorithm {
private:
    long long best_cost;
    std::vector<int> best_path;

public:
    RandomAlgorithm();
    void run(const TSPInstance& instance, const ConfigManager& config) override;
    long long getBestCost() const override;
    std::vector<int> getBestPath() const override;
};
