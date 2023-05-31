#include <vector>
#include <limits>

#include "src/rmqs/rmq.h"
#include "src/types.h"

class Naive_rmq : Rmq_answerer {
  public:
    Naive_rmq(const std::vector<int>& in) : 
      input(in),
      n(in.size()),
      indices(n * n) {

    }

    void init(std::vector<int>& in) {
      for (Index i = 0; i < n; i++) {
        for (Index j = i; j < n; j++) {
          indices.at(i * n + j) = brute_force_rmq(in, i, j);
        } 
      }
    }

    Index rmq(Index start, Index end) {
      return indices[start * n + end];
    }

  public:
    Index brute_force_rmq(const std::vector<int>& in, Index start, Index end) const {
      Index min_index = start;
      int min = in[min_index];
      for (Index i = start + 1; i <= end; i++) {
        if (in[i] < min) {
          min = in[i];
          min_index = i;
        }
      }
      return min_index;
    }

  private:
    const std::vector<int> input;
    const Index n;
    std::vector<Index> indices;
};