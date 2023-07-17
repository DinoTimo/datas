#include <vector>
#include <cmath>

#include <string>
#include "src/types.h"
#include "src/utils.h"
#include "rmq_answerer.h"

#pragma once

namespace rmq {
  class Nlogn_rmq : public Rmq_answerer {
    private: 
      const std::vector<Element> A;
      const Index n;
      const Index logn;
      std::vector<std::vector<int>> M;

    public:
      Nlogn_rmq(const std::vector<Element>& input) :
          A(input),
          n(A.size()),
          logn(std::floor(std::log(n))),
          M(0) {
        M.reserve(n);
        for (int i = 0; i < n; i++) {
          M.push_back(std::vector<int>(logn, -1));
        }
      }

      void init() {
        for (int l = 0; l < logn; l++) {
          for (int x = 0; x < n; x++) {
            determineM(x, l);
          }
        }
      }

      Index query(const Index& s, const Index& e) const {
        Index l = std::floor(std::log(e - s + 1));
        Index m1 = subquery(s, l);
        Index m2 = subquery(e - std::pow(2, l) + 1, l);
        return argmin(m1, m2);
      }

      int get_space_usage() const {
        return sizeof(Element) * 8 * (n * logn + n);
      }

    private:
      int determineM(const Index& x, Index l) {
        if (x >= n) {
          return -1;
        }
        if (l == 0) {
          M[x][l] = x;
          return x;
        }
        if (M[x][l] < 0) {
          int m1 = determineM(x, l - 1);
          int m2 = determineM(x + std::pow(2, l - 1), l - 1);
          M[x][l] = argmin(m1, m2);
        }
        return M[x][l];
      }

      Index subquery(const Index& x, const Index l) const {
        return argmin(M[x]                     [l - 1], 
                      M[x + std::pow(2, l - 1)][l - 1]);
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