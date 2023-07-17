#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

#include "src/types.h"
#include "src/utils.h"

#pragma once

namespace bv {
  constexpr size_t len = 64; //bits in a word
  using Word = uint64_t;

  class Bitvector {
    private:
      Index n;
      std::vector<Word> bit_vector;
      Index block_size;
      Index super_block_size;
      std::vector<int> super_blocks;
      std::vector<int> blocks;
    
    public:
      Bitvector(std::vector<bool> input) : 
          n(input.size()),
          bit_vector((n + len - 1)/ len) {
      
        Word word = 0;
        size_t word_id = 0;
        //fill up the array from left to right
        //each word i is constructed by adding each bit and then shifting left repeatedly.
        for (int i = 0; i < input.size(); i++) {
          word += input[i];
          bool new_word_reached = (i > 0 && i % len == len - 1) || i == input.size() - 1;
          if (!new_word_reached) {
            word = word << 1;
          }
          if (new_word_reached) {
            bit_vector[word_id] = word;
            word_id++;
            word = 0;
          }
        }
      }

      Bitvector(Index size) : 
          n(size),
          bit_vector((n + len - 1)/ len, 0) {
      
      }

      void init() {
        return;
        // not rly implemented for now, i fucked it up, sorry
        // rank and select is calculated from scratch each time.
        /*
        size_t count = 0;
        for (Word word : bit_vector) {
          for (int i = 0; i < len; i++) {
            super_blocks[count / super_block_size] += (word >> (len - 1 - i)) & 1;
            count++;
          }
        }
        */
      }

      bool get(Index i) const {
        Word word = bit_vector[i / len];
        bool bit = (word >> (len - 1 - (i % len))) & 1ULL;
        return bit;
      }

      void set(Index i, bool bit) {
        Word word = bit_vector[i / len];
        Index bit_index = i % len;
        if (bit) {
          Word mask = 1;
          mask = mask << (len - 1 - bit_index);
          word = word | mask;
          bit_vector[i / len] = word;
        } else {
          Word mask = 1;
          mask = mask << (len - 1 - bit_index);
          mask = ~mask;
          word = word & mask;
          bit_vector[i / len] = word;
        }
      }

      int select(bool bit, int occs) const {
        if (occs < 0) {
          return -1;
        }
        if (occs == 0) {
          return 0;
        }
        int bits_found = 0;
        int word_id = 0;
        for (Word word : bit_vector) {
          for (int i = 0; i < len && bits_found < occs; i++) {
            if (((word >> (len - 1 - i)) & 1) == bit) {
              bits_found++;
            }
            if (bits_found == occs) {
              return word_id * len + i;
            }
          }
          word_id++;
        }
        return -1;
      }

      int rank(bool b, int index) const {
        if (!b) {
          return index - rank(1, index);
        }
        int ones_found = 0;
        int count = 0;
        for (Word word : bit_vector) {
          for (int i = 0; i < len && count < index; i++) {
            ones_found += (word >> (len - i - 1)) & 1;
            count++;
          }
        }
        return ones_found;
      }
  };
}