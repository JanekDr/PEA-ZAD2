#pragma once
#include <vector>
#include <iostream>
#include "TSPInstance.h"
#include "ConfigManager.h"
#include "Timer.h"

class IAlgorithm {
public:
    virtual ~IAlgorithm() = default;
    virtual void run(const TSPInstance& instance, const ConfigManager& config) = 0;
    virtual long long getBestCost() const = 0;
    virtual std::vector<int> getBestPath() const = 0;

protected:
    static void displayProgress(int current, int total, const std::string& label, bool enabled) {
        if (!enabled) return;
        static int last_percent = -1;
        int percent = (total > 0) ? (current * 100) / total : 100;
        if (percent > last_percent) {
            std::cout << "\r[" << label << "] Postep: " << percent << "%" << std::flush;
            last_percent = percent;
            if (percent >= 100) {
                std::cout << std::endl;
                last_percent = -1;
            }
        }
    }
};
