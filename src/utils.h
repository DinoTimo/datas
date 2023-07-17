#include <vector>
#include <chrono>
#include <string>
#include <iostream>

#pragma once

void assert(bool b, std::string message) {
  if (!b) {
    std::cerr << "Assertion failed: " << message << std::endl;
    std::exit(-1);
  }
}

class Timer {
  using time = std::chrono::time_point<std::chrono::system_clock>;
  private:
    std::vector<time> q;

  public:
    void start() {
      q.push_back(std::chrono::system_clock::now());
    }

    double interval() {
      time now = std::chrono::system_clock::now();
      std::chrono::duration<double> diff = now - q[q.size() - 1];
      q.push_back(now);
      return diff.count();
    }

    double end() {
      time after = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = after - q[0];
      std::cerr << "Total time: " << elapsed_seconds.count() << "s\n";
      return elapsed_seconds.count();
    }

};