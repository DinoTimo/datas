#include <vector>
#include <limits>

#include "src/types.h"
#include "src/rmqs/rmq_answerer.h"
#include "src/utils.h"

#pragma once

namespace rmq {
  class Naive_rmq : public Rmq_answerer {
    public:
      Naive_rmq(const std::vector<Rmq_Element>& in) : 
        input(in),
        n(in.size()),
        indices(n * n) { }

      void init() {
        for (Index i = 0; i < n; i++) {
          for (Index j = i; j < n; j++) {
            indices.at(i * n + j) = brute_force_rmq(input, i, j);
          } 
        }
      }

      Index query(const Index& start, const Index& end) const {
        assert(start <= indices.at(start * n + end) && indices.at(start * n + end) <= end, "Illegal rmq answer");
        return indices.at(start * n + end);
      }

      int get_space_usage() const {
        return indices.size() * sizeof(Index) * 8;
      }

    public:
      Index brute_force_rmq(const std::vector<Rmq_Element>& in, const Index& start, const Index& end) const {
        Index min_index = start;
        int min = in.at(min_index);
        for (Index i = start + 1; i <= end; i++) {
          if (in.at(i) < min) {
            min = in.at(i);
            min_index = i;
          }
        }
        return min_index;
      }

    private:
      const std::vector<Rmq_Element> input;
      const Index n;
      std::vector<Index> indices;
  };

  class No_Storage_rmq : public Rmq_answerer {
    public:
      No_Storage_rmq(const std::vector<Rmq_Element>& in) : 
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

    private:
      const std::vector<Rmq_Element> input;
  };
}