#include <vector>
#include <limits>

#include "src/types.h"
#include "pd_answerer.h"
#include "src/utils.h"

#pragma once

namespace pd {
  class Naive_pd : public Pd_answerer {
    public:
      Naive_pd(const std::vector<Element>& in) : 
        input(in),
        n(in.size()) { }

      void init() { }

      Element query(const Element& el) const {
        Index i = binary_search(el);
        if (i <= 0) {
          return -1;
        }
        return input[i - 1];
      }

      Index binary_search(const Element& el) const {
        Index lower = 0;
        Index upper = input.size();
        while (lower < upper) {
          Index middle = (upper + lower) / 2;
          if (input[middle] <= el) {
            lower = middle + 1;
          } else {
            upper = middle;
          }
        }
        return lower;
      }

      int get_space_usage() const {
        return sizeof(Element) * 8 * n;
      }

    private:
      const std::vector<Element> input;
      const Index n;
  };
}