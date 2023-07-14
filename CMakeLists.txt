project(datas)
cmake_minimum_required(VERSION 3.0)
# include(CTest)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(datas src/main.cpp)

# add_test(NAME naive_rmq_constant_time_test COMMAND naive)