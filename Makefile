CXXFLAGS += -O3 -march=native --std=c++17 -Wall -Wextra

all: bench HandRanks.dat

bench: bench.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

HandRanks.dat: generate_table
	./generate_table

generate_table: twoplustwo/*.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) bench generate_table HandRanks.dat
