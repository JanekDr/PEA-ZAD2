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

    // Komparator dla std::priority_queue (dla Lowest Cost)
    struct CompareNode {
        bool operator()(const BBNode* const& n1, const BBNode* const& n2) {
            // Priority queue bierze największy element jako top. Zależy nam na najmniejszym koszcie.
            if (n1->current_cost == n2->current_cost) {
                // remis rozstrzygamy plusem dla głębszych w drzewie (bliżej liści)
                return n1->level < n2->level;
            }
            return n1->current_cost > n2->current_cost;
        }
    };
};

class BranchAndBound : public IAlgorithm {
private:
    long long best_cost;
    std::vector<int> best_path;

    // Konkretne warianty implementacji
    void runBFS(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSStack(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSRecursive(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runLC(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);

    // Rekurencja dla DFS
    void exploreDFSRec(BBNode* current_node, const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);

public:
    BranchAndBound();
    virtual ~BranchAndBound();
    void run(const TSPInstance& instance, const ConfigManager& config) override;
    long long getBestCost() const override;
    std::vector<int> getBestPath() const override;
};
