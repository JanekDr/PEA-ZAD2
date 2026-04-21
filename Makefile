CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -I./include
SRCS = main.cpp src/ConfigManager.cpp src/TSPInstance.cpp src/CsvWriter.cpp src/RNNAlgorithm.cpp src/NNAlgorithm.cpp src/RandomAlgorithm.cpp src/BranchAndBound.cpp
EXEC = zadanie2

LDFLAGS = 

ifeq ($(OS),Windows_NT)
	LDFLAGS += -lpsapi
	EXEC = zadanie2.exe
endif

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(EXEC)
