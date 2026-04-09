#pragma once
#include "IAlgorithm.h"
#include <vector>
#include <queue>
#include <stack>

struct BBNode {
    std::vector<int> path;
    std::vector<std::vector<int>> reduced_matrix;
    long long lower_bound;
    int vertex;
    int level;

    // Komparator dla std::priority_queue (dla Lowest Cost)
    struct CompareNode {
        bool operator()(const BBNode* const& n1, const BBNode* const& n2) {
            // Priority queue bierze największy element jako top. My chcemy najmniejszy.
            if (n1->lower_bound == n2->lower_bound) {
                // remis rozstrzygamy plusem dla glebszych w drzewie (lepiej dochodzic do lisci)
                return n1->level < n2->level;
            }
            return n1->lower_bound > n2->lower_bound;
        }
    };
};

class BranchAndBound : public IAlgorithm {
private:
    long long best_cost;
    std::vector<int> best_path;
    double execution_time_ms;

    // Pomocnicze do redukcji
    long long reduceMatrix(std::vector<std::vector<int>>& matrix, int dimension);
    
    // Konkretne warianty implementacji
    void runBFS(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSStack(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runDFSRecursive(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);
    void runLC(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress);

    // Rekurencja dla DFS
    void exploreDFSRec(BBNode* current_node, int dimension, bool show_progress);

public:
    BranchAndBound();
    virtual ~BranchAndBound();
    void run(const TSPInstance& instance, const ConfigManager& config) override;
    long long getBestCost() const override;
    std::vector<int> getBestPath() const override;
    double getExecutionTimeMs() const override;
};
