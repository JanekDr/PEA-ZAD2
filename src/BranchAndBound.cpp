#include "BranchAndBound.h"
#include "RNNAlgorithm.h"
#include "Timer.h"
#include "ConfigManager.h"
#include <limits>
#include <iostream>
#include <algorithm>

BranchAndBound::BranchAndBound() : best_cost(-1) {}
BranchAndBound::~BranchAndBound() {}

void BranchAndBound::run(const TSPInstance& instance, const ConfigManager& config) {
    int dimension = instance.getDimension();
    const auto& matrix = instance.getMatrix();
    
    best_cost = std::numeric_limits<long long>::max();
    best_path.clear();

    if (config.use_rnn_upper_bound) {
        RNNAlgorithm rnn;
        ConfigManager tempConfig = config;
        tempConfig.show_progress = false; 
        
        rnn.run(instance, tempConfig);
        best_cost = rnn.getBestCost();
        best_path = rnn.getBestPath();
        if (config.show_progress) {
            std::cout << "[B&B] Poczatkowe gorne ograniczenie z RNN: " << best_cost << std::endl;
        }
    }

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
}

void BranchAndBound::runBFS(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    std::queue<BBNode*> q;
    
    BBNode* root = new BBNode();
    root->path.push_back(0);
    root->current_cost = 0;
    root->vertex = 0;
    root->level = 1;
    
    q.push(root);

    long long nodes_visited = 0;
    
    while (!q.empty()) {
        BBNode* current = q.front();
        q.pop();
        nodes_visited++;

        if (show_progress && nodes_visited % 100000 == 0) {
            std::cout << "\r[BB_BFS] Odwiedzone wezly: " << nodes_visited << " | Aktualny best: " << best_cost << std::flush;
        }

        if (current->current_cost >= best_cost) {
            delete current;
            continue;
        }

        if (current->level == dimension) {
            int edge_back = initial_matrix[current->vertex][0];
            if (edge_back >= 0) {
                long long final_cost = current->current_cost + edge_back;
                if (final_cost < best_cost) {
                    best_cost = final_cost;
                    best_path = current->path;
                }
            }
            delete current;
            continue;
        }

        for (int i = 1; i < dimension; i++) {
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                
                int edge_cost = initial_matrix[current->vertex][i];
                if (edge_cost < 0) continue;
                
                long long child_cost = current->current_cost + edge_cost;
                
                if (child_cost < best_cost) {
                    BBNode* child = new BBNode();
                    child->path = current->path;
                    child->path.push_back(i);
                    child->level = current->level + 1;
                    child->vertex = i;
                    child->current_cost = child_cost;

                    q.push(child);
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
    root->path.push_back(0);
    root->current_cost = 0;
    root->vertex = 0;
    root->level = 1;
    
    s.push(root);

    long long nodes_visited = 0;
    
    while (!s.empty()) {
        BBNode* current = s.top();
        s.pop();
        nodes_visited++;

        if (show_progress && nodes_visited % 100000 == 0) {
            std::cout << "\r[BB_DFS_STACK] Odwiedzone wezly: " << nodes_visited << " | Aktualny best: " << best_cost << std::flush;
        }

        if (current->current_cost >= best_cost) {
            delete current;
            continue;
        }

        if (current->level == dimension) {
            int edge_back = initial_matrix[current->vertex][0];
            if (edge_back >= 0) {
                long long final_cost = current->current_cost + edge_back;
                if (final_cost < best_cost) {
                    best_cost = final_cost;
                    best_path = current->path;
                }
            }
            delete current;
            continue;
        }

        for (int i = 1; i < dimension; i++) {
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                
                int edge_cost = initial_matrix[current->vertex][i];
                if (edge_cost < 0) continue; 
                
                long long child_cost = current->current_cost + edge_cost;

                if (child_cost < best_cost) {
                    BBNode* child = new BBNode();
                    child->path = current->path;
                    child->path.push_back(i);
                    child->level = current->level + 1;
                    child->vertex = i;
                    child->current_cost = child_cost;

                    s.push(child);
                }
             }
        }
        delete current;
    }
    if (show_progress) std::cout << std::endl;
}

void BranchAndBound::exploreDFSRec(BBNode* current_node, const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    if (current_node->current_cost >= best_cost) {
        return;
    }

    if (current_node->level == dimension) {
        int edge_back = initial_matrix[current_node->vertex][0];
        if (edge_back >= 0) {
            long long final_cost = current_node->current_cost + edge_back;
            if (final_cost < best_cost) {
                best_cost = final_cost;
                best_path = current_node->path;
            }
        }
        return;
    }

    for (int i = 1; i < dimension; i++) {
         if (std::find(current_node->path.begin(), current_node->path.end(), i) == current_node->path.end()) {
             
            int edge_cost = initial_matrix[current_node->vertex][i];
            if (edge_cost < 0) continue; 
            
            long long child_cost = current_node->current_cost + edge_cost;

            if (child_cost < best_cost) {
                BBNode* child = new BBNode();
                child->path = current_node->path;
                child->path.push_back(i);
                child->level = current_node->level + 1;
                child->vertex = i;
                child->current_cost = child_cost;

                exploreDFSRec(child, initial_matrix, dimension, show_progress);
                delete child;
            }
         }
    }
}

void BranchAndBound::runDFSRecursive(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    BBNode* root = new BBNode();
    root->path.push_back(0);
    root->current_cost = 0;
    root->vertex = 0;
    root->level = 1;
    
    exploreDFSRec(root, initial_matrix, dimension, show_progress);
    delete root;
}

void BranchAndBound::runLC(const std::vector<std::vector<int>>& initial_matrix, int dimension, bool show_progress) {
    std::vector<BBNode*> active_nodes;
    
    BBNode* root = new BBNode();
    root->path.push_back(0);
    root->current_cost = 0;
    root->vertex = 0;
    root->level = 1;
    
    active_nodes.push_back(root);

    long long nodes_visited = 0;
    
    while (!active_nodes.empty()) {
        int best_index = 0;
        for (size_t i = 1; i < active_nodes.size(); ++i) {
            if (active_nodes[i]->current_cost < active_nodes[best_index]->current_cost) {
                best_index = i;
            } else if (active_nodes[i]->current_cost == active_nodes[best_index]->current_cost) {
                if (active_nodes[i]->level > active_nodes[best_index]->level) {
                    best_index = i;
                }
            }
        }

        BBNode* current = active_nodes[best_index];
        active_nodes.erase(active_nodes.begin() + best_index);

        nodes_visited++;

        if (show_progress && nodes_visited % 5000 == 0) {
            std::cout << "\r[BB_LC_MANUAL] Odwiedzone: " << nodes_visited << " | Aktualny best: " << best_cost << " | Rozpatrywany koszt: " << current->current_cost << std::flush;
        }

        if (current->current_cost >= best_cost) {
            delete current;
            continue;
        }

        if (current->level == dimension) {
            int edge_back = initial_matrix[current->vertex][0];
            if (edge_back >= 0) {
                long long final_cost = current->current_cost + edge_back;
                if (final_cost < best_cost) {
                    best_cost = final_cost;
                    best_path = current->path;
                }
            }
            delete current;
            continue;
        }

        for (int i = 1; i < dimension; i++) {
             if (std::find(current->path.begin(), current->path.end(), i) == current->path.end()) {
                
                int edge_cost = initial_matrix[current->vertex][i];
                if (edge_cost < 0) continue;

                long long child_cost = current->current_cost + edge_cost;

                if (child_cost < best_cost) {
                    BBNode* child = new BBNode();
                    child->path = current->path;
                    child->path.push_back(i);
                    child->level = current->level + 1;
                    child->vertex = i;
                    child->current_cost = child_cost;

                    active_nodes.push_back(child);
                }
             }
        }
        delete current;
    }
    
    if (show_progress) std::cout << std::endl;
}

long long BranchAndBound::getBestCost() const { return best_cost; }
std::vector<int> BranchAndBound::getBestPath() const { return best_path; }
