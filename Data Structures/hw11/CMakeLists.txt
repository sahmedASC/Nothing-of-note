cmake_minimum_required(VERSION 3.14)
project(hw11)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw11 performance.cpp performance_linked_list.cpp performance_bst.cpp performance_hash_table.cpp performance_priority_queue.cpp)