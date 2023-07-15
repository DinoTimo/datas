#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "src/types.h"
#include "rmq_pretty_printer.h"


namespace rmq {

  class Rmq_input_parser {
  private:
    std::vector<Rmq_Element> A;
    Index n;
    std::vector<std::pair<Index, Index>> requests;

  public:
    Rmq_input_parser() : A(0), n(0), requests(0) { }

    const std::vector<Rmq_Element>& get_array() const {
      return A;
    }

    const Index& get_n() {
      return n;
    } 

    const std::vector<std::pair<Index, Index>>& get_requests() const {
      return requests;
    }


    void read_input(std::string path) {
      std::ifstream input(path);
      std::string line;
      getline(input, line);
      n = std::stoi(line);
      int row_count = 0;
      while (row_count < n && getline(input, line)) {
        Rmq_Element curr = std::stoull(line);
        A.push_back(curr);
        row_count++;
      }
      
      while (getline(input, line)) {
        int comma_pos = line.find(",");
        Index a = std::stoi(line.substr(0, comma_pos));
        Index b = std::stoi(line.substr(comma_pos + 1));
        requests.push_back(std::pair<Index, Index>{a, b});
      }
    }

  };
}