CXX=g++
CXXFLAGS=-Wall

BIN=bin
SOL_FILES=$(wildcard sol_*.cpp)
TARGETS=$(patsubst %.cpp,$(BIN)/%,$(SOL_FILES))

all: $(BIN) $(TARGETS)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%: %.cpp main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN)/*

