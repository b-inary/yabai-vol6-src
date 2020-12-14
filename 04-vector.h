#pragma once
#include "03-hash_table.h"
#include "07-fastest.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

vector<vector<int>> comb(52, vector<int>(7));
vector<uint16_t> vec(133784560);

uint16_t evaluate_vector(const int *hand) {
  int sorted[7];
  copy(hand, hand + 7, sorted);
  sort_7(sorted);
  int key = comb[sorted[0]][0] + comb[sorted[1]][1] + comb[sorted[2]][2] + comb[sorted[3]][3]
          + comb[sorted[4]][4] + comb[sorted[5]][5] + comb[sorted[6]][6];
  return vec[key];
}

uint64_t benchmark_vector() {
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
                sum += evaluate_vector(hand);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}

void initialize_comb_table() {
  for (int i = 0; i < 52; ++i) {
    comb[i][0] = i;
    for (int j = 1; j < 7; ++j) {
      comb[i][j] = comb[i][j - 1] * (i - j) / (j + 1);
    }
  }
}

void initialize_vector() {
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
                int key = comb[i][0] + comb[j][1] + comb[k][2] + comb[m][3]
                        + comb[n][4] + comb[p][5] + comb[q][6];
                vec[key] = evaluate_fastest(hand);
              }
            }
          }
        }
      }
    }
  }
}
