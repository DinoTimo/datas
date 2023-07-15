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
    rmq::run(argv[2], argv[3]);
  } else {
    std::cerr << "ERROR: Illegal data structure. Expected either 'pd' or 'rmq', but got: " << argv[1] << std::endl;
  }
  return 0;
}
