#pragma once
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

const size_t num_elements = 32487834;
vector<int> hand_ranks(num_elements);

int evaluate_twoplustwo(const int *hand) {
  int p = 53;
  for (int i = 0; i < 7; ++i) {
    p = hand_ranks[hand[i] + p + 1];
  }
  return p;
}

uint64_t benchmark_twoplustwo() {
  uint64_t sum = 0;

  for (int i = 1; i <= 46; ++i) {
    int p1 = hand_ranks[i + 53];
    for (int j = i + 1; j <= 47; ++j) {
      int p2 = hand_ranks[j + p1];
      for (int k = j + 1; k <= 48; ++k) {
        int p3 = hand_ranks[k + p2];
        for (int m = k + 1; m <= 49; ++m) {
          int p4 = hand_ranks[m + p3];
          for (int n = m + 1; n <= 50; ++n) {
            int p5 = hand_ranks[n + p4];
            for (int p = n + 1; p <= 51; ++p) {
              int p6 = hand_ranks[p + p5];
              for (int q = p + 1; q <= 52; ++q) {
                int p7 = hand_ranks[q + p6];
                sum += p7;
              }
            }
          }
        }
      }
    }
  }

  return sum;
}

void initialize_hand_ranks() {
  ifstream ifs("HandRanks.dat", ios_base::binary);
  ifs.read(reinterpret_cast<char *>(hand_ranks.data()), num_elements * sizeof(int));
}
