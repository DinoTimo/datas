#include <iostream>
#include <string.h>

#include "src/types.h"
#include "rmqs/rmq.h"
#include "rmqs/naive/naive_rmq.h"

int main(int argc, char** argv){
  if (argc != 4) {
    std::cerr << "ERROR: Illegal number of arguments. Expected 4, but got: " << argc << std::endl;
    return -1;
  }
  if (strcmp("pd",argv[1]) == 0) {
    
  } else if (strcmp("rmq",argv[1]) == 0) {
    std::vector<int> A = {8, 2, 5, 1, 9, 11, 10, 20, 22, 4};
    Naive_rmq rmq(A);
    rmq.init(A);
    
    std::cout << "rmq(0,9)=" << rmq.rmq(0, 9) << std::endl;
    std::cout << "rmq(0,2)=" << rmq.rmq(0, 2) << std::endl;
    std::cout << "rmq(4,8)=" << rmq.rmq(4, 8) << std::endl;
  } else {
    std::cerr << "ERROR: Illegal data structure. Expected either 'pd' or 'rmq', but got: " << argv[1] << std::endl;
  }
  return 0;
}
