#include "CsvWriter.h"
#include <fstream>
#include <iostream>
#include <iomanip>

CsvWriter::CsvWriter(const std::string& filename) : filename(filename) {}

void CsvWriter::writeHeader() {
    std::ifstream infile(filename);
    bool exists = infile.good();
    infile.close();

    if (!exists) {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << "Dimension;Algorithm;Cost;Time[ms]\n";
            file.close();
        }
    }
}

void CsvWriter::writeRow(int dimension, const std::string& algorithm, long long cost, double time_ms) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << dimension << ";" 
             << algorithm << ";" 
             << cost << ";" 
             << std::fixed << std::setprecision(3) << time_ms << "\n";
        file.close();
    } else {
        std::cerr << "Nie udaje sie zapisac wyniku do CSV!" << std::endl;
    }
}
