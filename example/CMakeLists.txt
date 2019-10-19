add_library(bxdata SHARED
  raw_hit.h
  raw_hit.cc
  raw_data.h
  raw_data.cc
  raw_hit.ipp
  raw_data.ipp
  the_serializable.cc
  )
target_include_directories(bxdata PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bxdata PUBLIC Bayeux::Bayeux)

add_executable(bxdata-example bxdata-example.cc)
target_link_libraries(bxdata-example PRIVATE bxdata Bayeux::Bayeux)

if(BUILD_TESTING)
  add_test(NAME bxdata-example
    COMMAND bxdata-example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

