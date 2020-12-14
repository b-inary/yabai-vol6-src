#pragma once
#include "01-naive.h"
#include "06-cactus_kev_consts.h"
#include <algorithm>
#include <cstdint>
using namespace std;

unsigned find(unsigned u) {
    u += 0xe91aaa35;
    u ^= u >> 16;
    u += u << 8;
    u ^= u >> 4;
    unsigned a = (u + (u << 2)) >> 19;
    unsigned b = (u >> 8) & 0x1ff;
    return a ^ hash_adjust[b];
}

uint16_t evaluate_cactus_kev_5hand_internal(const int *hand) {
    int q = (hand[0] | hand[1] | hand[2] | hand[3] | hand[4]) >> 16;
    uint16_t s;
    if (hand[0] & hand[1] & hand[2] & hand[3] & hand[4] & 0xf000) return flushes[q];
    if ((s = unique5[q])) return s;
    return hash_values[find(
      (hand[0] & 0xff) * (hand[1] & 0xff) * (hand[2] & 0xff) * (hand[3] & 0xff) * (hand[4] & 0xff)
    )];
}

uint16_t evaluate_cactus_kev_5hand_fast(const int *hand) {
  return 7463 - evaluate_cactus_kev_5hand_internal(hand);
}

uint16_t evaluate_cactus_kev_7hand_fast(const int *hand) {
  uint16_t best = 0;
  int subhand[5];
  for (int i = 0; i < 21; ++i) {
    for (int j = 0; j < 5; ++j) {
      subhand[j] = hand[comb_7_5[i][j]];
    }
    best = max(best, evaluate_cactus_kev_5hand_fast(subhand));
  }
  return best;
}

uint16_t evaluate_cactus_kev(const int *hand) {
  int converted[7];
  for (int i = 0; i < 7; ++i) converted[i] = deck[hand[i]];
  return evaluate_cactus_kev_7hand_fast(converted);
}

uint64_t benchmark_cactus_kev() {
  uint64_t sum = 0;
  int hand[7];

  for (int i = 0; i < 46; ++i) {
    hand[0] = deck[i];
    for (int j = i + 1; j < 47; ++j) {
      hand[1] = deck[j];
      for (int k = j + 1; k < 48; ++k) {
        hand[2] = deck[k];
        for (int m = k + 1; m < 49; ++m) {
          hand[3] = deck[m];
          for (int n = m + 1; n < 50; ++n) {
            hand[4] = deck[n];
            for (int p = n + 1; p < 51; ++p) {
              hand[5] = deck[p];
              for (int q = p + 1; q < 52; ++q) {
                hand[6] = deck[q];
                sum += evaluate_cactus_kev_7hand_fast(hand);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}
