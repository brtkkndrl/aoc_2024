CXX=g++
CXXFLAGS=-Wall

SOL_FILES=$(wildcard sol_*.cpp)
TARGETS=$(SOL_FILES:.cpp=.exe)

all: $(TARGETS)

%.exe: %.cpp main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
