CXX = g++
CXXFLAGS = -O3 -std=c++17 -I./algorithms
TARGET = matrix_multiplication

SUB_DIR = ./algorithms
SRCS = matrix_multiplication.cpp $(wildcard $(SUB_DIR)/*.cpp)
OBJS = matrix_multiplication.o $(patsubst $(SUB_DIR)/%.cpp, %.o, $(wildcard $(SUB_DIR)/*.cpp))

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
	rm -f data/matrix_output/naive/*.txt
	rm -f data/matrix_output/strassen/*.txt
	rm -f data/plots/*.png
	rm -f data/tablas/*.tex
	rm -f data/measurements/*.csv
	rm -f data/matrix_input/*.txt