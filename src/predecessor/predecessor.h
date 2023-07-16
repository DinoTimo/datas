
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "src/utils.h"
#include "src/pretty_printer.h"
#include "pd_input_parser.h"
#include "naive_pd.h"

#pragma once

namespace pd {

  void run(std::string in, std::string out) {
    Timer timer;
    std::stringstream result_line;
    result_line << "RESULT algo=pd name=timo_fritsch";


    Pd_input_parser input_parser;
    Log::pretty::print_banner("START PD-INPUT-PARSING");
    timer.start();
    input_parser.read_input(in);
    Log::pretty::print_interval(timer.interval(), "PD-INPUT-PARSING");

    //DECIDE HERE WHICH RMQ DATA STRUCTURE TO USE

    Naive_pd pd_struc(input_parser.get_array());

    //begin setup
    Log::pretty::print_banner("START PRECALCULATION");
    timer.interval();
    pd_struc.init();
    double precalc_time = timer.interval();
    Log::pretty::print_interval(precalc_time, "PRECALCULATION");
    //end setup

   
    //begin execution
    Log::pretty::print_banner("START EXECUTION");
    timer.interval();
    pd_struc.run_requests(input_parser.get_requests(), out);
    double exec_time = timer.interval();
    Log::pretty::print_interval(exec_time, "EXECUTION");
    //end execution

    result_line << " time=" << precalc_time + exec_time;
    result_line << " space=" << pd_struc.get_space_usage();
    
    result_line << " exec_time=" << exec_time;
    result_line << " precalc_time=" << precalc_time;
    result_line << " num_requests=" << input_parser.get_requests().size();
    result_line << " n=" << input_parser.get_n();

    std::ofstream out_file;
    out_file.open(out);
    for (int i = 0; i < input_parser.get_requests().size(); i++) {
      out_file << pd_struc.get_answers()[i] << "\n";
      std::cerr << "pred(" << input_parser.get_requests()[i] << ") = " << pd_struc.get_answers()[i] << "\n";
    }
    out_file.close();
    std::cout << result_line.str() << std::endl;
  }
}