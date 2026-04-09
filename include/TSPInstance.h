#pragma once
#include <string>
#include <vector>

class TSPInstance {
private:
    int dimension;
    std::vector<std::vector<int>> dist_matrix;

public:
    TSPInstance();
    void loadFromFile(const std::string& filename);
    int getDimension() const;
    long long calculatePathCost(const std::vector<int>& path) const;
    double getMemoryUsageMB() const;
    const std::vector<std::vector<int>>& getMatrix() const;
    void generateRandomAndSave(const std::string& filename, int size, bool symmetric);
};
