#include <iostream>

#include "src/types.h"
#include "rmqs/rmq.h"
#include "rmqs/naive/naive_rmq.h"

int main(int argc, char** argv){
  std::vector<int> A = {8, 2, 5, 1, 9, 11, 10, 20, 22, 4};
  Naive_rmq rmq(A);
  rmq.init(A);
  
	std::cout << "Hello World" << std::endl;
  std::cout << "rmq(0,9)=" << rmq.rmq(0, 9) << std::endl;
  std::cout << "rmq(0,2)=" << rmq.rmq(0, 2) << std::endl;
  std::cout << "rmq(4,8)=" << rmq.rmq(4, 8) << std::endl;
	return 0;
}
