CXX = g++
CXXFLAGS = -O3 -std=c++17 -I./algorithms
TARGET = sorting

SUB_DIR = ./algorithms
SRCS = sorting.cpp $(wildcard $(SUB_DIR)/*.cpp)
OBJS = sorting.o $(patsubst $(SUB_DIR)/%.cpp, %.o, $(wildcard $(SUB_DIR)/*.cpp))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

sorting.o: sorting.cpp	
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: $(SUB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)
	python3 scripts/plot_generator.py
	
clean:
	rm -f *.o $(TARGET)
	rm -f data/array_output/mergesort/*.txt
	rm -f data/array_output/patiencesort/*.txt
	rm -f data/array_output/quicksort/*.txt
	rm -f data/array_output/sort/*.txt
	rm -f data/array_input/*.txt
	rm -f data/plots/*.png
	rm -f data/tablas/*.tex
	rm -f data/measurements/*.csv
