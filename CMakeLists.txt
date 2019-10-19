# - Top level CMakeLists.txt for datatools ex_serializable example program
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(BayeuxSerialization)

# - Bayeux :
find_package(Bayeux 3.4.0 REQUIRED)

add_library(bxdata SHARED
  raw_hit.h
  raw_hit.cc
  raw_data.h
  raw_data.cc
  raw_hit.ipp
  raw_data.ipp
  the_serializable.cc
  )
target_include_directories(bxdata PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(bxdata PUBLIC Bayeux::Bayeux)

add_executable(bxdata-example bxdata-example.cc)
target_link_libraries(bxdata-example PRIVATE bxdata Bayeux::Bayeux)

include(CTest)
if(BUILD_TESTING)
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tests/bxdata-example)
  add_test(NAME bxdata-example
    COMMAND bxdata-example
    WORKING_DIRECTORY tests/bxdata-example)
endif()

