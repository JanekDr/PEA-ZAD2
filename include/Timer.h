#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool is_running;

public:
    Timer() : is_running(false) {}

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        is_running = true;
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
        is_running = false;
    }

    /// Zwraca czas w milisekundach (jako double by uchwycić ułamki ms)
    double getElapsedMs() const {
        auto end = is_running ? std::chrono::high_resolution_clock::now() : end_time;
        std::chrono::duration<double, std::milli> duration = end - start_time;
        return duration.count();
    }
};
