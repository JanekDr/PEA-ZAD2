#pragma once
#include <string>

class CsvWriter {
private:
    std::string filename;

public:
    CsvWriter(const std::string& filename);
    void writeHeader();
    void writeRow(int dimension, const std::string& algorithm, long long cost, double time_ms);
};
