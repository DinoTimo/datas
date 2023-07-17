#include <vector>
#include <cmath>
#include <algorithm>
#include "src/types.h"
#include "src/bitvectors/bitvector.h"

#pragma once


namespace pd {
  class Elias_pd {
    private:
      const std::vector<Element> input;
      Element u;
      Index n;
      size_t upper_bit_count;
      size_t lower_bit_count;
      bv::Bitvector upper;
      std::vector<Element> lower;


    public:
      Elias_pd(const std::vector<Element>& array) :
          input(array),
          u(std::max_element(std::begin(array), std::end(array))[0] + 1),
          n(input.size()),
          upper_bit_count(std::ceil(std::log(n))),
          lower_bit_count(std::ceil(std::log(u) - std::log(n))),
          upper(2 * n + 1),
          lower(n, 0) { }

      void init() {
        for (size_t i = 0; i < n; i++) {
          Element el = input[i];
          Element upper_el = el >> lower_bit_count;
          upper.set(i + upper_el, 1);

          Element lower_mask = ~0;
          lower_mask = (lower_mask >> lower_bit_count) << lower_bit_count;
          lower_mask = ~lower_mask;
          Element lower_el = el & lower_mask;
          lower.at(i) = lower_el;
        }
      }
       
      /**
       * I dont know how this works, im sorry.
      */
      Element pred(Element e) {
        Element upper_x = e >> lower_bit_count;
        Index p = upper.select(0, upper_x);

        for (Element el : lower) {
      
        }
        return 0;
      }


  };
}