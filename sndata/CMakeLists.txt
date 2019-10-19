add_library(sndata SHARED hit.h hit.cc)
target_compile_features(sndata PUBLIC cxx_std_11)
target_include_directories(sndata PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
target_link_libraries(sndata PUBLIC Bayeux::Bayeux)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
