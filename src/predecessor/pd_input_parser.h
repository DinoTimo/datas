#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "src/types.h"
#include "src/pretty_printer.h"

#pragma once

namespace pd {

  class Pd_input_parser {
  private:
    std::vector<Element> A;
    Index n;
    std::vector<Element> requests;

  public:
    Pd_input_parser() : A(0), n(0), requests(0) { }

    const std::vector<Element>& get_array() const {
      return A;
    }

    const Index& get_n() {
      return n;
    } 

    const std::vector<Element>& get_requests() const {
      return requests;
    }

    void read_input(std::string path) {
      std::ifstream input(path);
      std::string line;
      getline(input, line);
      n = std::stoi(line);
      int row_count = 0;
      while (row_count < n && getline(input, line)) {
        Element curr = std::stoull(line);
        A.push_back(curr);
        row_count++;
      }
      
      while (getline(input, line)) {
        Element request = std::stoull(line);
        requests.push_back(request);
      }
    }

  };
}