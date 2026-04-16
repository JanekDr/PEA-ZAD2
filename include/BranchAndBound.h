#pragma once
#include "IAlgorithm.h"
#include <vector>
#include <queue>
#include <stack>

struct BBNode {
    std::vector<int> path;
    long long current_cost;
    int vertex;
    int level;

};

class BranchAndBound : public IAlgorithm {
private:
    long long best_cost;
    std::vector<int> best_path;

    void runBFS(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSStack(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSRecursive(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runLC(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);

    void exploreDFSRec(BBNode* current_node, const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);

public:
    BranchAndBound();
    virtual ~BranchAndBound();
    void run(const TSPInstance& instance, const ConfigManager& config) override;
    long long getBestCost() const override;
    std::vector<int> getBestPath() const override;
};
