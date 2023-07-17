#include <vector>
#include <cmath>

#include <string>
#include "src/types.h"
#include "src/utils.h"
#include "rmq_answerer.h"
#include "nlogn_rmq.h"

#pragma once

namespace rmq {
  class N_rmq : public Rmq_answerer {
    private: 
      const std::vector<Element> A;
      const Index n;
      const Index logn;
      const Index s;
      const Index m;
      std::vector<std::vector<Index>> backward_block_indizes;
      std::vector<std::vector<Index>> forward_block_indizes;
      std::vector<Index> block_min_indizes;

    public:
      N_rmq(const std::vector<Element>& input) :
          A(input),
          n(A.size()),
          logn(std::ceil(std::log(n))),
          s(4),//s(std::ceil(logn / 4.0f)),
          m(std::ceil((1.0f * n) / (1.0f *  s))),
          backward_block_indizes(0),
          forward_block_indizes(0),
          block_min_indizes(m) {
        backward_block_indizes.reserve(m);
        forward_block_indizes.reserve(m);
        for (int i = 0; i < m; i++) {
          backward_block_indizes.push_back(std::vector<Index>(s, 0));
          forward_block_indizes.push_back(std::vector<Index>(s, 0));
        }
      }

      void init() {
        Index curr_forward_min_index = 0;
        for (int i = 0; i < n; i++) {
          Index forward_block_index = i / s;
          curr_forward_min_index = argmin(curr_forward_min_index, i);
          forward_block_indizes[forward_block_index][i % s] = curr_forward_min_index;
        }
        Index curr_backward_min_index = n - 1;
        for (int i = n - 1; i >= 0; i--) {
          Index backward_block_index = i / s;
          curr_backward_min_index = argmin(curr_backward_min_index, i);
          backward_block_indizes[backward_block_index][i % s] = curr_backward_min_index;
        }      
      }

      Index query(const Index& start, const Index& end) const {
        Index result = ~0;
        Index start_block_index  = start / s;
        Index end_block_index = end / s;
        //pre query
        Index m1 = backward_query(start, start_block_index);
        //main query
        Index m2 = main_query(start_block_index + 1, end_block_index - 1);
        //post query
        Index m3 = forward_query(end_block_index, end);
        return argmin(m1, argmin(m2, m3));
      }

      int get_space_usage() const {
        return sizeof(Index) * 8 * (m + 2 * m * s);
      }


    private:
      Index backward_query(const Index& start, const Index& end_block_index) const {
        return backward_block_indizes[end_block_index][start % s];
      }
      
      Index main_query(const Index& start_block_index, const Index& end_block_index) const {
        Index min_index = block_min_indizes[start_block_index];
        for (int i = start_block_index + 1; i <= end_block_index; i++) {
          min_index = argmin(min_index, block_min_indizes[i]);
        }
        return 0;
      }

      Index forward_query(const Index& start_block_index, const Index& end) const {
        return forward_block_indizes[start_block_index][end % s];
      }





      Index argmin(const Index& a, const Index& b) const {
        if (A[a] < A[b]) {
          return a;
        } else {
          return b;
        }
        // compiler improves this
      }
  };
}