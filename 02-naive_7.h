#pragma once
#include <cstdint>
using namespace std;

#define count_ones(x) __builtin_popcount(x)
#define msb(x) (1 << (__builtin_clz(x) ^ 31))

int keep_n_msb(int x, int n) {
  int result = 0;
  for (int i = 0; i < n; ++i) {
    int m = msb(x);
    x ^= m;
    result |= m;
  }
  return result;
}

int find_straight(int rankset) {
  const int wheel = 0b1'0000'0000'1111;
  int is_straight = rankset & (rankset << 1) & (rankset << 2)
                  & (rankset << 3) & (rankset << 4);
  if (is_straight) {
    return keep_n_msb(is_straight, 1);
  } else if ((rankset & wheel) == wheel) {
    return 1 << 3;
  } else {
    return 0;
  }
}

int evaluate_naive_7(const int *hand) {
  int rankset = 0;
  int rankset_suit[4] = { 0, 0, 0, 0 };
  int rankset_of_count[5] = { 0, 0, 0, 0, 0 };
  int count[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  for (int i = 0; i < 7; ++i) {
    int suit = hand[i] % 4;
    int rank = hand[i] / 4;
    rankset |= 1 << rank;
    rankset_suit[suit] |= 1 << rank;
    ++count[rank];
  }

  for (int rank = 0; rank < 13; ++rank) {
    rankset_of_count[count[rank]] |= 1 << rank;
  }

  int is_flush = -1;
  for (int i = 0; i < 4; ++i) {
    if (count_ones(rankset_suit[i]) >= 5) is_flush = i;
  }

  int is_straight;

  if (is_flush >= 0) {
    if ((is_straight = find_straight(rankset_suit[is_flush]))) {
      // straight flush
      return (8 << 26) | is_straight;
    } else {
      // flush
      return (5 << 26) | keep_n_msb(rankset_suit[is_flush], 5);
    }
  } else if (rankset_of_count[4]) {
    // four of a kind
    int remaining = keep_n_msb(rankset ^ rankset_of_count[4], 1);
    return (7 << 26) | (rankset_of_count[4] << 13) | remaining;
  } else if (count_ones(rankset_of_count[3]) == 2) {
    // full house
    int trips = keep_n_msb(rankset_of_count[3], 1);
    int pair = rankset_of_count[3] ^ trips;
    return (6 << 26) | (trips << 13) | pair;
  } else if (rankset_of_count[3] && rankset_of_count[2]) {
    // full house
    int pair = keep_n_msb(rankset_of_count[2], 1);
    return (6 << 26) | (rankset_of_count[3] << 13) | pair;
  } else if ((is_straight = find_straight(rankset))) {
    // straight
    return (4 << 26) | is_straight;
  } else if (rankset_of_count[3]) {
    // three of a kind
    int remaining = keep_n_msb(rankset_of_count[1], 2);
    return (3 << 26) | (rankset_of_count[3] << 13) | remaining;
  } else if (count_ones(rankset_of_count[2]) >= 2) {
    // two pair
    int pairs = keep_n_msb(rankset_of_count[2], 2);
    int remaining = keep_n_msb(rankset ^ pairs, 1);
    return (2 << 26) | (pairs << 13) | remaining;
  } else if (rankset_of_count[2]) {
    // one pair
    int remaining = keep_n_msb(rankset_of_count[1], 3);
    return (1 << 26) | (rankset_of_count[2] << 13) | remaining;
  } else {
    // high card
    return (0 << 26) | keep_n_msb(rankset, 5);
  }
}

uint64_t benchmark_naive_7() {
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
                sum += evaluate_naive_7(hand);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}
