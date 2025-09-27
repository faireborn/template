cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(nlp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

fetchcontent_declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

fetchcontent_makeavailable(Catch2)

set(TEST_SRCS
  util_test.cc)

string(REPLACE "_test.cc" "" TEST_BASENAMES "${TEST_SRCS}")

foreach(name ${TEST_BASENAMES})
  add_executable(${name}_test ${name}_test.cc ${name}.cc ${name}.h)
  target_link_libraries(${name}_test Catch2WithMain)
endforeach()

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

foreach(name ${TEST_BASENAMES})
  catch_discover_tests(${name}_test)
endforeach()
