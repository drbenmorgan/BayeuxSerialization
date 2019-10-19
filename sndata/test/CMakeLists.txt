# - Create Catch testing utility library
add_library(LocalCatch STATIC catch/catch.hpp catch/catch-main.cpp)
target_compile_features(LocalCatch PUBLIC cxx_std_11)
target_include_directories(LocalCatch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/catch)

# - Tests
add_executable(hit_t hit_t.cc)
target_link_libraries(hit_t PRIVATE sndata LocalCatch)
add_test(NAME hit_t COMMAND hit_t -s)
