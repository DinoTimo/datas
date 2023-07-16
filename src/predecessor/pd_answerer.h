#include <vector>
#include <string>

#include "src/types.h"


#pragma once

namespace pd {
  class Pd_answerer {
    private:
      std::vector<Element> answers;
    public:
      void init(std::vector<int> vec);
      virtual Element query(const Element& element) const = 0;
      virtual int get_space_usage() const = 0;

      const std::vector<Element>& get_answers() const {
        return answers;
      }

      void run_requests(const std::vector<Element>& requests, const std::string& outfile) {
        answers.reserve(requests.size());
        for (const Element& request : requests) {
          const Index answer = query(request);
          answers.push_back(answer);
        }
      }
  };
}