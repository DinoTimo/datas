#include <string>
#include <iostream>
#include <vector>
#include <chrono>

namespace Log {
  namespace pretty  {
    size_t title_width = 50;
    size_t duration_width = 30;

    void printDivider() {
      for (size_t i = 0; i < title_width; i++) {
        std::cerr << "-";
      }
      std::cerr << std::endl;
    }

    void print_interval(double interval, std::string title) {
      std::cerr << "  " << title << " duration: ";
      for (int i = 2 + title.length() + 11; i < duration_width; i++) {
        std::cerr << " ";
      }
      std::cerr << interval << "s" <<std::endl;
    }

    void print(std::string s) {
      std::cerr << s << std::endl;
    }

    void printTitle(std::string title) {
      size_t title_len = title.size();
      if (title_len >= title_width) {
        std::cout << title << "\n";
        return;
      }

      size_t i = 0;
      for (; i < (title_width - title_len + 1) / 2; i++) {
        std::cout << "-";
      } 
      std::cout << title;
      for (; i < (title_width - title_len); i++) {
        std::cout << "-";
      }
      std::cout << "\n";
    }

    void print_banner(std::string title) {
      printDivider();
      printTitle(title);
      printDivider();
    }
    
  }
}