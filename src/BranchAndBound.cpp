#include "BranchAndBound.h"
#include "RNNAlgorithm.h"
#include "Timer.h"
#include "ConfigManager.h"
#include <limits>
#include <iostream>
#include <algorithm>

BranchAndBound::BranchAndBound() : best_cost(-1), execution_time_ms(0.0) {}
BranchAndBound::~BranchAndBound() {}

long long BranchAndBound::reduceMatrix(std::vector<std::vector<int>>& matrix, int dimension) {
    long long reduction_cost = 0;
    
    // Minimum w wierszach
    for (int i = 0; i < dimension; i++) {
        int row_min = std::numeric_limits<int>::max();
        for (int j = 0; j < dimension; j++) {
            if (matrix[i][j] >= 0 && matrix[i][j] < row_min) {
                row_min = matrix[i][j];
            }
        }
        if (row_min > 0 && row_min != std::numeric_limits<int>::max()) {
            reduction_cost += row_min;
            for (int j = 0; j < dimension; j++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] -= row_min;
                }
            }
        }
    }

    // Minimum w kolumnach
    for (int j = 0; j < dimension; j++) {
        int col_min = std::numeric_limits<int>::max();
        for (int i = 0; i < dimension; i++) {
            if (matrix[i][j] >= 0 && matrix[i][j] < col_min) {
                col_min = matrix[i][j];
            }
        }
        if (col_min > 0 && col_min != std::numeric_limits<int>::max()) {
            reduction_cost += col_min;
            for (int i = 0; i < dimension; i++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] -= col_min;
                }
            }
        }
    }

    return reduction_cost;
}

void BranchAndBound::run(const TSPInstance& instance, const ConfigManager& config) {
    int dimension = instance.getDimension();
    const auto& matrix = instance.getMatrix();
    
    best_cost = std::numeric_limits<long long>::max();
    best_path.clear();

    // Obliczanie początkowego ograniczenia jeśli żądane
    if (config.use_rnn_upper_bound) {
        RNNAlgorithm rnn;
        // Wylaczamy progress dla pomocniczego RNN
        ConfigManager tempConfig = config;
        tempConfig.show_progress = false; 
        
        rnn.run(instance, tempConfig);
        best_cost = rnn.getBestCost();
        best_path = rnn.getBestPath();
        if (config.show_progress) {
            std::cout << "[B&B] Poczatkowe gorne ograniczenie z RNN: " << best_cost << std::endl;
        }
    }

    Timer timer;
    timer.start();

    if (config.algorithm == "BB_BFS") {
        runBFS(matrix, dimension, config.show_progress);
    } else if (config.algorithm == "BB_DFS_STACK") {
        runDFSStack(matrix, dimension, config.show_progress);
    } else if (config.algorithm == "BB_DFS_REC") {
        runDFSRecursive(matrix, dimension, config.show_progress);
    } else if (config.algorithm == "BB_LC") {
        runLC(matrix, dimension, config.show_progress);
    } else {
        std::cerr << "Nie znany wariant Branch and Bound!\n";
    }

    timer.stop();
    execution_time_ms = timer.getElapsedMs();
}

void BranchAndBound::runBFS(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    std::queue<BBNode*> q;
    
    BBNode* root = new BBNode();
    root->reduced_matrix = initial_matrix;
    // Blokujemy przekątną dla obliczeń
    for(int i=0; i<dimension; ++i) root->reduced_matrix[i][i] = -1;
    root->path.push_back(0); // Zawsze zaczynamy od wierzcholka 0
    root->lower_bound = reduceMatrix(root->reduced_matrix, dimension);
    root->vertex = 0;
    root->level = 1;
    
    q.push(root);

    long long nodes_visited = 0;
    
    while (!q.empty()) {
        BBNode* current = q.front();
        q.pop();
        nodes_visited++;

        if (show_progress && nodes_visited % 10000 == 0) {
            std::cout << "\r[BB_BFS] Odwiedzone wezly: " << nodes_visited << " | Aktualny best: " << best_cost << std::flush;
        }

        // Przycinanie (Pruning)
        if (current->lower_bound >= best_cost) {
            delete current;
            continue;
        }

        // Lisc
        if (current->level == dimension) {
            long long final_cost = current->lower_bound + (current->reduced_matrix[current->vertex][0] >= 0 ? current->reduced_matrix[current->vertex][0] : 0);
            if(initial_matrix[current->vertex][0] < 0 && final_cost > 0) {
               // sciezka niemozliwa
               delete current;
               continue;
            }
            if (final_cost < best_cost) {
                best_cost = final_cost;
                best_path = current->path;
            }
            delete current;
            continue;
        }

        // Generowanie dzieci
        for (int i = 1; i < dimension; i++) {
             // Sprawdzamy, czy wierzchołek nie był odwiedzony
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                
                if (current->reduced_matrix[current->vertex][i] < 0) continue; // brak polaczenia

                BBNode* child = new BBNode();
                child->path = current->path;
                child->path.push_back(i);
                child->level = current->level + 1;
                child->vertex = i;
                child->reduced_matrix = current->reduced_matrix;

                // Koszt przejścia
                int edge_cost = current->reduced_matrix[current->vertex][i];

                // Blokada wiersza i kolumny odwiedzonego przejscia
                for (int k = 0; k < dimension; ++k) {
                    child->reduced_matrix[current->vertex][k] = -1;
                    child->reduced_matrix[k][i] = -1;
                }
                // Zablokuj powrót z nowego wierzchołka pętli
                child->reduced_matrix[i][0] = -1;

                long long child_reduction = reduceMatrix(child->reduced_matrix, dimension);
                child->lower_bound = current->lower_bound + edge_cost + child_reduction;

                if (child->lower_bound < best_cost) {
                    q.push(child);
                } else {
                    delete child;
                }
             }
        }
        delete current;
    }
    if (show_progress) std::cout << std::endl;
}

void BranchAndBound::runDFSStack(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    std::stack<BBNode*> s;
    
    BBNode* root = new BBNode();
    root->reduced_matrix = initial_matrix;
    for(int i=0; i<dimension; ++i) root->reduced_matrix[i][i] = -1;
    root->path.push_back(0);
    root->lower_bound = reduceMatrix(root->reduced_matrix, dimension);
    root->vertex = 0;
    root->level = 1;
    
    s.push(root);

    long long nodes_visited = 0;
    
    while (!s.empty()) {
        BBNode* current = s.top();
        s.pop();
        nodes_visited++;

        if (show_progress && nodes_visited % 10000 == 0) {
            std::cout << "\r[BB_DFS_STACK] Odwiedzone wezly: " << nodes_visited << " | Aktualny best: " << best_cost << std::flush;
        }

        if (current->lower_bound >= best_cost) {
            delete current;
            continue;
        }

        if (current->level == dimension) {
            long long final_cost = current->lower_bound + (current->reduced_matrix[current->vertex][0] >= 0 ? current->reduced_matrix[current->vertex][0] : 0);
             if(initial_matrix[current->vertex][0] < 0 && final_cost > 0) {
               delete current;
               continue;
            }
            if (final_cost < best_cost) {
                best_cost = final_cost;
                best_path = current->path;
            }
            delete current;
            continue;
        }

        for (int i = 1; i < dimension; i++) {
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                if (current->reduced_matrix[current->vertex][i] < 0) continue;

                BBNode* child = new BBNode();
                child->path = current->path;
                child->path.push_back(i);
                child->level = current->level + 1;
                child->vertex = i;
                child->reduced_matrix = current->reduced_matrix;

                int edge_cost = current->reduced_matrix[current->vertex][i];

                for (int k = 0; k < dimension; ++k) {
                    child->reduced_matrix[current->vertex][k] = -1;
                    child->reduced_matrix[k][i] = -1;
                }
                child->reduced_matrix[i][0] = -1;

                child->lower_bound = current->lower_bound + edge_cost + reduceMatrix(child->reduced_matrix, dimension);

                if (child->lower_bound < best_cost) {
                    s.push(child);
                } else {
                    delete child;
                }
             }
        }
        delete current;
    }
    if (show_progress) std::cout << std::endl;
}

void BranchAndBound::exploreDFSRec(BBNode* current_node, int dimension, bool show_progress) {
    if (current_node->lower_bound >= best_cost) {
        return;
    }

    if (current_node->level == dimension) {
        long long final_cost = current_node->lower_bound + (current_node->reduced_matrix[current_node->vertex][0] >= 0 ? current_node->reduced_matrix[current_node->vertex][0] : 0);
        if (final_cost < best_cost) {
            best_cost = final_cost;
            best_path = current_node->path;
        }
        return;
    }

    for (int i = 1; i < dimension; i++) {
         if (std::find(current_node->path.begin(), current_node->path.end(), i) == current_node->path.end()) {
            if (current_node->reduced_matrix[current_node->vertex][i] < 0) continue;

            BBNode* child = new BBNode();
            child->path = current_node->path;
            child->path.push_back(i);
            child->level = current_node->level + 1;
            child->vertex = i;
            child->reduced_matrix = current_node->reduced_matrix;

            int edge_cost = current_node->reduced_matrix[current_node->vertex][i];

            for (int k = 0; k < dimension; ++k) {
                child->reduced_matrix[current_node->vertex][k] = -1;
                child->reduced_matrix[k][i] = -1;
            }
            child->reduced_matrix[i][0] = -1;

            child->lower_bound = current_node->lower_bound + edge_cost + reduceMatrix(child->reduced_matrix, dimension);

            if (child->lower_bound < best_cost) {
                exploreDFSRec(child, dimension, show_progress);
            }
            delete child;
         }
    }
}

void BranchAndBound::runDFSRecursive(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    BBNode* root = new BBNode();
    root->reduced_matrix = initial_matrix;
    for(int i=0; i<dimension; ++i) root->reduced_matrix[i][i] = -1;
    root->path.push_back(0);
    root->lower_bound = reduceMatrix(root->reduced_matrix, dimension);
    root->vertex = 0;
    root->level = 1;
    
    exploreDFSRec(root, dimension, show_progress);
    delete root;
}

void BranchAndBound::runLC(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    std::priority_queue<BBNode*, std::vector<BBNode*>, BBNode::CompareNode> pq;
    
    BBNode* root = new BBNode();
    root->reduced_matrix = initial_matrix;
    for(int i=0; i<dimension; ++i) root->reduced_matrix[i][i] = -1;
    root->path.push_back(0);
    root->lower_bound = reduceMatrix(root->reduced_matrix, dimension);
    root->vertex = 0;
    root->level = 1;
    
    pq.push(root);

    long long nodes_visited = 0;
    
    while (!pq.empty()) {
        BBNode* current = pq.top();
        pq.pop();
        nodes_visited++;

        if (show_progress && nodes_visited % 10000 == 0) {
            std::cout << "\r[BB_LC] Odwiedzone wezly: " << nodes_visited << " | Aktualny best: " << best_cost << " | Top queue UB: " << current->lower_bound << std::flush;
        }

        if (current->lower_bound >= best_cost) {
            delete current;
            continue;
        }

        if (current->level == dimension) {
             long long final_cost = current->lower_bound + (current->reduced_matrix[current->vertex][0] >= 0 ? current->reduced_matrix[current->vertex][0] : 0);
             if(initial_matrix[current->vertex][0] < 0 && final_cost > 0) {
               delete current;
               continue;
            }
            if (final_cost < best_cost) {
                best_cost = final_cost;
                best_path = current->path;
            }
            delete current;
            continue;
        }

        for (int i = 1; i < dimension; i++) {
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                if (current->reduced_matrix[current->vertex][i] < 0) continue;

                BBNode* child = new BBNode();
                child->path = current->path;
                child->path.push_back(i);
                child->level = current->level + 1;
                child->vertex = i;
                child->reduced_matrix = current->reduced_matrix;

                int edge_cost = current->reduced_matrix[current->vertex][i];

                for (int k = 0; k < dimension; ++k) {
                    child->reduced_matrix[current->vertex][k] = -1;
                    child->reduced_matrix[k][i] = -1;
                }
                child->reduced_matrix[i][0] = -1;

                child->lower_bound = current->lower_bound + edge_cost + reduceMatrix(child->reduced_matrix, dimension);

                if (child->lower_bound < best_cost) {
                    pq.push(child);
                } else {
                    delete child;
                }
             }
        }
        delete current;
    }
    
    if (show_progress) std::cout << std::endl;
}

long long BranchAndBound::getBestCost() const { return best_cost; }
std::vector<int> BranchAndBound::getBestPath() const { return best_path; }
double BranchAndBound::getExecutionTimeMs() const { return execution_time_ms; }
