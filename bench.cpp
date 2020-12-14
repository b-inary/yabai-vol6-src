#include "01-naive.h"
#include "02-naive_7.h"
#include "03-hash_table.h"
#include "04-vector.h"
#include "05-twoplustwo.h"
#include "06-cactus_kev.h"
#include "07-fastest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <chrono>
#include <cstdint>
using namespace std;

void initialize() {
  initialize_hash_table();
  initialize_comb_table();
  initialize_vector();
  initialize_hand_ranks();
}

template <class Func>
void benchmark_sequential(Func func) {
  cout << "starting benchmark..." << endl;
  auto start = chrono::system_clock::now();
  uint64_t sum = func();
  chrono::duration<double> dur = chrono::system_clock::now() - start;
  cout << "finished benchmark.\n";
  cout << "elapsed time: " << dur.count() << "[s]\n";
  cout << "throughput: " << static_cast<uint64_t>(133'784'560 / dur.count()) << "\n";
  cout << "checksum: " << sum << endl;
}

template <class Func>
void benchmark_random(Func func, const vector<int> &random_hands) {
  cout << "starting benchmark...\n";
  uint64_t sum = 0;
  auto start = chrono::system_clock::now();
  for (int i = 0; i < 700'000'000; i += 7) {
    sum += func(random_hands.data() + i);
  }
  chrono::duration<double> dur = chrono::system_clock::now() - start;
  cout << "finished benchmark.\n";
  cout << "elapsed time: " << dur.count() << "[s]\n";
  cout << "throughput: " << static_cast<uint64_t>(100'000'000 / dur.count()) << "\n";
  cout << "checksum: " << sum << "\n";
}

#define benchmark(method) \
  cout << "---\n"; \
  cout << "[" #method ": sequential]\n"; \
  benchmark_sequential(benchmark_ ## method); \
  cout << "---\n"; \
  cout << "[" #method ": random access]\n"; \
  benchmark_random(evaluate_ ## method, random_hands)

int main() {
  cout << "preparing random hands..." << endl;
  mt19937 gen;  // fix random seed
  vector<int> cards(52);
  iota(cards.begin(), cards.end(), 0);
  vector<int> random_hands(700'000'000);
  for (int i = 0; i < 700'000'000; i += 7) {
    sample(cards.begin(), cards.end(), random_hands.begin() + i, 7, gen);
    shuffle(random_hands.begin() + i, random_hands.begin() + i + 7, gen);
  }

  cout << "initializing objects..." << endl;
  initialize();

  benchmark(naive);
  benchmark(naive_7);
  benchmark(hash_table);
  benchmark(vector);
  benchmark(twoplustwo);
  benchmark(cactus_kev);
  benchmark(fastest);
}
