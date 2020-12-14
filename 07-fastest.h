#pragma once
#include "07-fastest_consts.h"
#include <vector>
#include <cstdint>
#include <emmintrin.h>
using namespace std;

const uint32_t rank_bases[] = {
  0x002000, 0x008001, 0x011000, 0x03a000, 0x091000, 0x176005, 0x366000, 0x41a013,
  0x47802e, 0x479068, 0x48c0e4, 0x48f211, 0x494493,
};

union HandData {
  struct {
    uint32_t rank_key;
    uint32_t suit_key;
    uint64_t bit_flag;
  } s;
  __m128i simd_reg;
};

const HandData cards[] = {
  {{ rank_bases[0], 0x1000'0000, 0x0000'0000'0000'0001 }},
  {{ rank_bases[0], 0x0100'0000, 0x0000'0000'0001'0000 }},
  {{ rank_bases[0], 0x0010'0000, 0x0000'0001'0000'0000 }},
  {{ rank_bases[0], 0x0001'0000, 0x0001'0000'0000'0000 }},
  {{ rank_bases[1], 0x1000'0000, 0x0000'0000'0000'0002 }},
  {{ rank_bases[1], 0x0100'0000, 0x0000'0000'0002'0000 }},
  {{ rank_bases[1], 0x0010'0000, 0x0000'0002'0000'0000 }},
  {{ rank_bases[1], 0x0001'0000, 0x0002'0000'0000'0000 }},
  {{ rank_bases[2], 0x1000'0000, 0x0000'0000'0000'0004 }},
  {{ rank_bases[2], 0x0100'0000, 0x0000'0000'0004'0000 }},
  {{ rank_bases[2], 0x0010'0000, 0x0000'0004'0000'0000 }},
  {{ rank_bases[2], 0x0001'0000, 0x0004'0000'0000'0000 }},
  {{ rank_bases[3], 0x1000'0000, 0x0000'0000'0000'0008 }},
  {{ rank_bases[3], 0x0100'0000, 0x0000'0000'0008'0000 }},
  {{ rank_bases[3], 0x0010'0000, 0x0000'0008'0000'0000 }},
  {{ rank_bases[3], 0x0001'0000, 0x0008'0000'0000'0000 }},
  {{ rank_bases[4], 0x1000'0000, 0x0000'0000'0000'0010 }},
  {{ rank_bases[4], 0x0100'0000, 0x0000'0000'0010'0000 }},
  {{ rank_bases[4], 0x0010'0000, 0x0000'0010'0000'0000 }},
  {{ rank_bases[4], 0x0001'0000, 0x0010'0000'0000'0000 }},
  {{ rank_bases[5], 0x1000'0000, 0x0000'0000'0000'0020 }},
  {{ rank_bases[5], 0x0100'0000, 0x0000'0000'0020'0000 }},
  {{ rank_bases[5], 0x0010'0000, 0x0000'0020'0000'0000 }},
  {{ rank_bases[5], 0x0001'0000, 0x0020'0000'0000'0000 }},
  {{ rank_bases[6], 0x1000'0000, 0x0000'0000'0000'0040 }},
  {{ rank_bases[6], 0x0100'0000, 0x0000'0000'0040'0000 }},
  {{ rank_bases[6], 0x0010'0000, 0x0000'0040'0000'0000 }},
  {{ rank_bases[6], 0x0001'0000, 0x0040'0000'0000'0000 }},
  {{ rank_bases[7], 0x1000'0000, 0x0000'0000'0000'0080 }},
  {{ rank_bases[7], 0x0100'0000, 0x0000'0000'0080'0000 }},
  {{ rank_bases[7], 0x0010'0000, 0x0000'0080'0000'0000 }},
  {{ rank_bases[7], 0x0001'0000, 0x0080'0000'0000'0000 }},
  {{ rank_bases[8], 0x1000'0000, 0x0000'0000'0000'0100 }},
  {{ rank_bases[8], 0x0100'0000, 0x0000'0000'0100'0000 }},
  {{ rank_bases[8], 0x0010'0000, 0x0000'0100'0000'0000 }},
  {{ rank_bases[8], 0x0001'0000, 0x0100'0000'0000'0000 }},
  {{ rank_bases[9], 0x1000'0000, 0x0000'0000'0000'0200 }},
  {{ rank_bases[9], 0x0100'0000, 0x0000'0000'0200'0000 }},
  {{ rank_bases[9], 0x0010'0000, 0x0000'0200'0000'0000 }},
  {{ rank_bases[9], 0x0001'0000, 0x0200'0000'0000'0000 }},
  {{ rank_bases[10], 0x1000'0000, 0x0000'0000'0000'0400 }},
  {{ rank_bases[10], 0x0100'0000, 0x0000'0000'0400'0000 }},
  {{ rank_bases[10], 0x0010'0000, 0x0000'0400'0000'0000 }},
  {{ rank_bases[10], 0x0001'0000, 0x0400'0000'0000'0000 }},
  {{ rank_bases[11], 0x1000'0000, 0x0000'0000'0000'0800 }},
  {{ rank_bases[11], 0x0100'0000, 0x0000'0000'0800'0000 }},
  {{ rank_bases[11], 0x0010'0000, 0x0000'0800'0000'0000 }},
  {{ rank_bases[11], 0x0001'0000, 0x0800'0000'0000'0000 }},
  {{ rank_bases[12], 0x1000'0000, 0x0000'0000'0000'1000 }},
  {{ rank_bases[12], 0x0100'0000, 0x0000'0000'1000'0000 }},
  {{ rank_bases[12], 0x0010'0000, 0x0000'1000'0000'0000 }},
  {{ rank_bases[12], 0x0001'0000, 0x1000'0000'0000'0000 }},
};

class Hand {
public:
  Hand() : data{{ 0, 0x3333'0000, 0 }} {}
  Hand(__m128i simd_reg) : data{.simd_reg = simd_reg} {}

  Hand add_card(int card) const {
    return Hand{_mm_add_epi64(data.simd_reg, cards[card].simd_reg)};
  }

  uint16_t evaluate() const {
    uint32_t is_flush = data.s.suit_key & 0x8888'0000;
    if (is_flush) {
      uint16_t flush_key = data.s.bit_flag >> (4 * __builtin_clz(is_flush));
      return lookup_flush[flush_key];
    } else {
      uint32_t hash_key = offset[data.s.rank_key >> 12] + data.s.rank_key;
      return lookup[hash_key];
    }
  }

private:
  HandData data;
};

uint16_t evaluate_fastest(const int *hand_ary) {
  Hand hand;
  for (int i = 0; i < 7; ++i) {
    hand = hand.add_card(hand_ary[i]);
  }
  return hand.evaluate();
}

uint64_t benchmark_fastest() {
  uint64_t sum = 0;
  Hand hand0;

  for (int i = 0; i < 46; ++i) {
    Hand hand1 = hand0.add_card(i);
    for (int j = i + 1; j < 47; ++j) {
      Hand hand2 = hand1.add_card(j);
      for (int k = j + 1; k < 48; ++k) {
        Hand hand3 = hand2.add_card(k);
        for (int m = k + 1; m < 49; ++m) {
          Hand hand4 = hand3.add_card(m);
          for (int n = m + 1; n < 50; ++n) {
            Hand hand5 = hand4.add_card(n);
            for (int p = n + 1; p < 51; ++p) {
              Hand hand6 = hand5.add_card(p);
              for (int q = p + 1; q < 52; ++q) {
                Hand hand7 = hand6.add_card(q);
                sum += hand7.evaluate();
              }
            }
          }
        }
      }
    }
  }

  return sum;
}
