#include <iostream>
#include <string.h>
#include <vector>

#include "src/types.h"
#include "rmqs/rmq.h"
#include "rmqs/naive_rmq.h"
#include "predecessor/predecessor.h"
#include "predecessor/elias_pd.h"

#include "rmqs/nlogn_rmq.h"
#include "rmqs/n_rmq.h"
#include "bitvectors/bitvector.h"

/**
 * The general procedure is the following:
 * 1. First command line arg is read
 * 2. the corresponding pd or rmq run method is chosen to run
 * 3. in each run method, first the input files are read, then the precalculation starts, and then the execution of the given request starts.
 *    the results are written to an in memory array. After every request has been executed, the results are written to the out file.
 * 
 * The data structures are structured similarly. The pd and rmq strucs both inherit from a respective super class called _answerer, which manages the interface to the outer run method.
 * The input is parsed with a respecitve _input_parser file.
 *  
 */
int main(int argc, char** argv){
  if (argc < 4) {
    std::cerr << "ERROR: Illegal number of arguments. Expected at least 4, but got: " << argc << std::endl;
    return -1;
  }
  if (strcmp("pd",argv[1]) == 0) {
    pd::run(argv[2], argv[3]);
  } else if (strcmp("rmq",argv[1]) == 0) {
    rmq::run(argv[2], argv[3]);
  } else {
    std::cerr << "ERROR: Illegal data structure. Expected either 'pd' or 'rmq', but got: " << argv[1] << std::endl;
  }
  return 0;
}
