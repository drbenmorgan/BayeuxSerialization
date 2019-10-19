# - Top level CMakeLists.txt for datatools ex_serializable example program
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(BayeuxSerialization)

include(CTest)

# - Bayeux :
find_package(Bayeux 3.4.0 REQUIRED)

# projects
add_subdirectory(example)
