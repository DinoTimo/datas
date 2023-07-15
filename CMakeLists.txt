project(datas)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
# include(CTest)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(datas src/main.cpp)

# add_test(NAME naive_rmq_constant_time_test COMMAND naive)