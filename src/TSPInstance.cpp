#include "TSPInstance.h"
#include <fstream>
#include <iostream>
#include <random>

TSPInstance::TSPInstance() : dimension(0) {}

void TSPInstance::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku: " << filename << std::endl;
        exit(1);
    }
    if (!(file >> dimension)) {
        std::cerr << "Blad: Plik jest pusty lub ma zly format!" << std::endl;
        exit(1);
    }
    dist_matrix.assign(dimension, std::vector<int>(dimension, 0));
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (!(file >> dist_matrix[i][j])) {
                std::cerr << "Blad: Nieoczekiwany koniec pliku! Brakuje danych w macierzy." << std::endl;
                exit(1);
            }
        }
    }
    file.close();
}

int TSPInstance::getDimension() const { return dimension; }

long long TSPInstance::calculatePathCost(const std::vector<int>& path) const {
    long long cost = 0;
    int n = path.size();
    if (n < 2) return 0;
    for (int i = 0; i < n - 1; ++i) {
        cost += dist_matrix[path[i]][path[i+1]];
    }
    cost += dist_matrix[path[n-1]][path[0]];
    return cost;
}

double TSPInstance::getMemoryUsageMB() const {
    return (dimension * dimension * sizeof(int)) / (1024.0 * 1024.0);
}

const std::vector<std::vector<int>>& TSPInstance::getMatrix() const { return dist_matrix; }

void TSPInstance::generateRandomAndSave(const std::string& filename, int size, bool symmetric) {
    dimension = size;
    dist_matrix.assign(dimension, std::vector<int>(dimension, 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (i == j) {
                dist_matrix[i][j] = -1;
            } else {
                if (symmetric && i > j) {
                    dist_matrix[i][j] = dist_matrix[j][i];
                } else {
                    dist_matrix[i][j] = dist(gen);
                }
            }
        }
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << dimension << "\n";
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                file << dist_matrix[i][j] << " ";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Wygenerowano nowa macierz i zapisano do: " << filename << std::endl;
    } else {
        std::cerr << "Blad przy probie zapisu wygenerowanej macierzy!" << std::endl;
        exit(1);
    }
}
