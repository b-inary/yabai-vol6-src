#pragma once
#include "07-fastest.h"
#include <unordered_map>
#include <algorithm>
#include <cstdint>
using namespace std;

unordered_map<uint64_t, uint16_t> hash_table;

void sort_2(int &a, int &b) {
  int minv = a < b ? a : b;
  int maxv = a >= b ? a : b;
  a = minv;
  b = maxv;
}

void sort_7(int *v) {
  sort_2(v[0], v[4]); sort_2(v[1], v[5]); sort_2(v[2], v[6]);
  sort_2(v[0], v[2]); sort_2(v[1], v[3]); sort_2(v[4], v[6]);
  sort_2(v[2], v[4]); sort_2(v[3], v[5]);
  sort_2(v[0], v[1]); sort_2(v[2], v[3]); sort_2(v[4], v[5]);
  sort_2(v[1], v[4]); sort_2(v[3], v[6]);
  sort_2(v[1], v[2]); sort_2(v[3], v[4]); sort_2(v[5], v[6]);
}

uint16_t evaluate_hash_table(const int *hand) {
  int sorted[7];
  copy(hand, hand + 7, sorted);
  sort_7(sorted);
  uint64_t lo = sorted[0] | (sorted[1] << 8) | (sorted[2] << 16) | (sorted[3] << 24);
  uint64_t hi = sorted[4] | (sorted[5] << 8) | (sorted[6] << 16);
  return hash_table[lo | (hi << 32)];
}

uint64_t benchmark_hash_table() {
  uint64_t sum = 0;
  int hand[7];

  for (int i = 0; i < 46; ++i) {
    hand[0] = i;
    for (int j = i + 1; j < 47; ++j) {
      hand[1] = j;
      for (int k = j + 1; k < 48; ++k) {
        hand[2] = k;
        for (int m = k + 1; m < 49; ++m) {
          hand[3] = m;
          for (int n = m + 1; n < 50; ++n) {
            hand[4] = n;
            for (int p = n + 1; p < 51; ++p) {
              hand[5] = p;
              for (int q = p + 1; q < 52; ++q) {
                hand[6] = q;
                sum += evaluate_hash_table(hand);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}

void initialize_hash_table() {
  int hand[7];

  for (int i = 0; i < 46; ++i) {
    hand[0] = i;
    for (int j = i + 1; j < 47; ++j) {
      hand[1] = j;
      for (int k = j + 1; k < 48; ++k) {
        hand[2] = k;
        for (int m = k + 1; m < 49; ++m) {
          hand[3] = m;
          for (int n = m + 1; n < 50; ++n) {
            hand[4] = n;
            for (int p = n + 1; p < 51; ++p) {
              hand[5] = p;
              for (int q = p + 1; q < 52; ++q) {
                hand[6] = q;
                uint64_t lo = i | (j << 8) | (k << 16) | (m << 24);
                uint64_t hi = n | (p << 8) | (q << 16);
                hash_table[lo | (hi << 32)] = evaluate_fastest(hand);
              }
            }
          }
        }
      }
    }
  }
}
