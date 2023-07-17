#include <vector>
#include <limits>

#include "src/types.h"
#include "src/rmqs/rmq_answerer.h"
#include "src/utils.h"

#pragma once

namespace rmq {
  class Naive_rmq : public Rmq_answerer {
    public:
      Naive_rmq(const std::vector<Element>& in) : 
        input(in) { }

      void init() {  }

      Index query(const Index& start, const Index& end) const {
        Index min_index = start;
        int min = input.at(min_index);
        for (Index i = start + 1; i <= end; i++) {
          if (input.at(i) < min) {
            min = input.at(i);
            min_index = i;
          }
        }
        assert(start <= min_index && min_index <= end, "Illegal rmq answer");
        return min_index;
      }

      int get_space_usage() const {
        return input.size() * sizeof(Element) * 8;
      }

    private:
      const std::vector<Element> input;
  };
}