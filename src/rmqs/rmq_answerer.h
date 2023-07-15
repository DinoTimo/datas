#include <vector>
#include <string>

#include "src/types.h"


#pragma once

namespace rmq {
  class Rmq_answerer {
    private:
      std::vector<Index> answer_indizes;
    public:
      void init(std::vector<int> vec);
      virtual Index query(const Index& start, const Index& end) const = 0;
      virtual int get_space_usage() const = 0;

      const std::vector<Index>& get_answer_indizes() const {
        return answer_indizes;
      }

      void run_requests(const std::vector<std::pair<Index, Index>>& requests, const std::string& outfile) {
        const int n = requests.size();
        answer_indizes.reserve(n);
        for (const std::pair<Index, Index>& request : requests) {
          const Index answer = query(request.first, request.second);
          answer_indizes.push_back(answer);
        }
      }
  };
}