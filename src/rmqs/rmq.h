#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "rmq_input_parser.h"
#include "naive_rmq.h"
#include "nlogn_rmq.h"
#include "src/utils.h"

#pragma once

namespace rmq {

  void run(std::string in, std::string out) {
    Timer timer;
    std::stringstream result_line;
    result_line << "RESULT algo=rmq name=timo_fritsch";
    rmq::Rmq_input_parser input_parser;

    Log::pretty::print_banner("START RMQ-INPUT-PARSING");
    timer.start();
    input_parser.read_input(in);
    Log::pretty::print_interval(timer.interval(), "RMQ-INPUT-PARSING");

    //DECIDE HERE WHICH RMQ DATA STRUCTURE TO USE

    Naive_rmq rmq_struc(input_parser.get_array());

    //Nlogn_rmq rmq_struc(input_parser.get_array());

    //begin setup
    Log::pretty::print_banner("START PRECALCULATION");
    timer.interval();
    rmq_struc.init();
    double precalc_time = timer.interval();
    Log::pretty::print_interval(precalc_time, "PRECALCULATION");
    //end setup

   
    //begin execution
    Log::pretty::print_banner("START EXECUTION");
    timer.interval();
    rmq_struc.run_requests(input_parser.get_requests(), out);
    double exec_time = timer.interval();
    Log::pretty::print_interval(exec_time, "EXECUTION");
    //end execution

    result_line << " time=" << precalc_time + exec_time;
    result_line << " space=" << rmq_struc.get_space_usage();
    
    result_line << " exec_time=" << exec_time;
    result_line << " precalc_time=" << precalc_time;
    result_line << " num_requests=" << input_parser.get_requests().size();
    result_line << " n=" << input_parser.get_n();

    std::ofstream out_file;
    out_file.open(out); 
    for (int i = 0; i < input_parser.get_requests().size(); i++) {
      out_file << rmq_struc.get_answer_indizes()[i] << "\n";
    }
    out_file.close();
    std::cout << result_line.str() << std::endl;
  }
}