cmake_minimum_required(VERSION 3.14)
project(algorithm VERSION 1.0 LANGUAGES C CXX)

add_executable(triangle)
target_compile_features(triangle PRIVATE cxx_std_23)

target_sources(triangle PRIVATE
  triangle.cc
)

enable_testing()
add_test(
  NAME test
  COMMAND bash -x ${CMAKE_CURRENT_LIST_DIR}/test/test.sh ${CMAKE_CURRENT_BINARY_DIR}/triangle ${CMAKE_CURRENT_LIST_DIR}/test/triangle/input00.txt ${CMAKE_CURRENT_LIST_DIR}/test/triangle/output00.txt
)
