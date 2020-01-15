cmake_minimum_required(VERSION 3.13)
project(hw10)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw10 main.cpp Job.h Job.cpp TimeQueue.h UrgentQueue.h UrgentQueue.cpp TimeQueue.cpp)