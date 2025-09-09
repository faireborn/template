cmake_minimum_required(VERSION 3.14)
project(algorithm VERSION 1.0 LANGUAGES C CXX)

set(TESTDIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB SUBDIRS RELATIVE ${TESTDIR} ${TESTDIR}/*)
set(TESTNAMES "")
foreach(subdir ${SUBDIRS})
  if(IS_DIRECTORY ${TESTDIR}/${subdir})
    list(APPEND TESTNAMES ${subdir})
  endif()
endforeach()

enable_testing()
foreach(testname ${TESTNAMES})
  add_executable(${testname})
  target_compile_features(${testname} PRIVATE cxx_std_23)

  target_sources(${testname} PRIVATE
    ${testname}.cc
  )

  file(GLOB INPUTS
    RELATIVE ${TESTDIR}/${testname} "${TESTDIR}/${testname}/input*.txt")
  file(GLOB OUTPUTS
    RELATIVE ${TESTDIR}/${testname} "${TESTDIR}/${testname}/output*.txt")

  foreach(input output IN ZIP_LISTS INPUTS OUTPUTS)
    add_test(
      NAME ${testname}-${input}
      COMMAND bash -x ${TESTDIR}/test.sh
      ${CMAKE_CURRENT_BINARY_DIR}/${testname}
      ${TESTDIR}/${testname}/${input}
      ${TESTDIR}/${testname}/${output}
    )
  endforeach()


endforeach()
