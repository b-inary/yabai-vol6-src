#pragma once
#include <algorithm>
#include <cstdint>
using namespace std;

#define count_ones(x) __builtin_popcount(x)

const int comb_7_5[21][5] = {
  { 0, 1, 2, 3, 4 },
  { 0, 1, 2, 3, 5 },
  { 0, 1, 2, 3, 6 },
  { 0, 1, 2, 4, 5 },
  { 0, 1, 2, 4, 6 },
  { 0, 1, 2, 5, 6 },
  { 0, 1, 3, 4, 5 },
  { 0, 1, 3, 4, 6 },
  { 0, 1, 3, 5, 6 },
  { 0, 1, 4, 5, 6 },
  { 0, 2, 3, 4, 5 },
  { 0, 2, 3, 4, 6 },
  { 0, 2, 3, 5, 6 },
  { 0, 2, 4, 5, 6 },
  { 0, 3, 4, 5, 6 },
  { 1, 2, 3, 4, 5 },
  { 1, 2, 3, 4, 6 },
  { 1, 2, 3, 5, 6 },
  { 1, 2, 4, 5, 6 },
  { 1, 3, 4, 5, 6 },
  { 2, 3, 4, 5, 6 },
};

int evaluate_naive_5(const int *hand) {
  int suitset = 0;
  int rankset = 0;
  int rankset_of_count[5] = { 0, 0, 0, 0, 0 };
  int rankcount[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  for (int i = 0; i < 5; ++i) {
    int suit = hand[i] % 4;
    int rank = hand[i] / 4;
    suitset |= 1 << suit;
    rankset |= 1 << rank;
    ++rankcount[rank];
  }

  for (int rank = 0; rank < 13; ++rank) {
    rankset_of_count[rankcount[rank]] |= 1 << rank;
  }

  bool is_flush = count_ones(suitset) == 1;
  int is_straight = rankset & (rankset << 1) & (rankset << 2)
                  & (rankset << 3) & (rankset << 4);
  if (rankset == 0b1'0000'0000'1111) is_straight = 1 << 3;

  if (is_flush && is_straight) {
    // straight flush
    return (8 << 26) | is_straight;
  } else if (rankset_of_count[4]) {
    // four of a kind
    return (7 << 26) | (rankset_of_count[4] << 13) | rankset_of_count[1];
  } else if (rankset_of_count[3] && rankset_of_count[2]) {
    // full house
    return (6 << 26) | (rankset_of_count[3] << 13) | rankset_of_count[2];
  } else if (is_flush) {
    // flush
    return (5 << 26) | rankset;
  } else if (is_straight) {
    // straight
    return (4 << 26) | is_straight;
  } else if (rankset_of_count[3]) {
    // three of a kind
    return (3 << 26) | (rankset_of_count[3] << 13) | rankset_of_count[1];
  } else if (rankset_of_count[2]) {
    // two pair or one pair
    int num_pairs = count_ones(rankset_of_count[2]);
    return (num_pairs << 26) | (rankset_of_count[2] << 13) | rankset_of_count[1];
  } else {
    // high card
    return (0 << 26) | rankset;
  }
}

int evaluate_naive(const int *hand) {
  int best = 0;
  int subhand[5];
  for (int i = 0; i < 21; ++i) {
    for (int j = 0; j < 5; ++j) {
      subhand[j] = hand[comb_7_5[i][j]];
    }
    best = max(best, evaluate_naive_5(subhand));
  }
  return best;
}

uint64_t benchmark_naive() {
  int hand[7];
  uint64_t sum = 0;

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
                sum += evaluate_naive(hand);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}
