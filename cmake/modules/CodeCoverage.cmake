# Copyright (c) 2012 - 2015, Lars Bilke
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

include(CMakeParseArguments)

find_program(GCOV_PATH gcov)
if(NOT GCOV_PATH)
  message(FATAL_ERROR "gcov not found! Aborting...")
endif()

find_program(LCOV_PATH lcov)
if(NOT LCOV_PATH)
  message(FATAL_ERROR "lcov not found! Aborting...")
endif()

if(NOT CMAKE_COMPILER_IS_GNUCXX)
  if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(FATAL_ERROR "Compiler '${CMAKE_CXX_COMPILER_ID}' is not supported ! Aborting...")
  endif()
endif()

if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Coverage"))
  message( WARNING "Code coverage results with an optimized (non-Debug) build may be misleading" )
endif()

set(CMAKE_CXX_FLAGS_COVERAGE "-g -O0 --coverage"
  CACHE
  STRING
  "Flags used by the C++ compiler during coverage builds."
  FORCE
  )

set(CMAKE_C_FLAGS_COVERAGE "-g -O0 --coverage"
  CACHE
  STRING
  "Flags used by the C compiler during coverage builds."
  FORCE )

set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "--coverage"
  CACHE
  STRING
  "Flags used for linking binaries during coverage builds."
  FORCE
  )

set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "--coverage"
  CACHE
  STRING
  "Flags used by the shared libraries linker during coverage builds."
  FORCE
  )

mark_as_advanced(
  CMAKE_CXX_FLAGS_COVERAGE
  CMAKE_C_FLAGS_COVERAGE
  CMAKE_EXE_LINKER_FLAGS_COVERAGE
  CMAKE_SHARED_LINKER_FLAGS_COVERAGE
  )

if(NOT TARGET "coverage")
  add_custom_target("coverage" ;
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

function(add_coverage TARGET_NAME)

  set(OPTIONS REPORT QUIET)
  set(SV_ARGUMENTS OUTPUT)
  set(MV_ARGUMENTS DEPENDENCIES SOURCE_DIRECTORIES COMMAND)
  cmake_parse_arguments(ADD_COVERAGE "${OPTIONS}" "${SV_ARGUMENTS}" "${MV_ARGUMENTS}" ${ARGN})

  if(${ADD_COVERAGE_OUTPUT})
    set(COVERAGE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Coverage/${ADD_COVERAGE_OUTPUT}")
  else()
    set(COVERAGE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Coverage/${TARGET_NAME}")
  endif()

  if(ADD_COVERAGE_QUIET)
    set(COVERAGE_QUIET_FLAG "-q")
  else()
    unset(COVERAGE_QUIET_FLAG)
  endif()

  if(ADD_COVERAGE_REPORT)
    set(COVERAGE_REPORT ON)
  else()
    set(COVERAGE_REPORT OFF)
  endif()

  set(COVERAGE_RAW_DATA "${COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}.raw")
  set(COVERAGE_CLEAN_DATA "${COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}.clean")
  set(COVERAGE_COMMENT_PREFIX "[CodeCoverage:${TARGET_NAME}]")
  set(COVERAGE_REPORT_DIRECTORY "${COVERAGE_OUTPUT_DIRECTORY}/report")
  set(COVERAGE_DEPENDENCIES "${ADD_COVERAGE_DEPENDENCIES}")
  set(COVERAGE_DRIVER "${ADD_COVERAGE_COMMAND}")

  set(COVERAGE_TARGET_NAME "coverage_${TARGET_NAME}")

  set_property(DIRECTORY APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES "${COVERAGE_OUTPUT_DIRECTORY}"
    )

  foreach(SOURCE_DIRECTORY IN LISTS ADD_COVERAGE_SOURCE_DIRECTORIES)
    list(APPEND EXTRACT_DIRECTORIES "'${SOURCE_DIRECTORY}'")
  endforeach()

  if(NOT TARGET ${COVERAGE_TARGET_NAME})
    string(REPLACE ";" " " DRIVER "${COVERAGE_DRIVER}")
    message(STATUS "Registering coverage target '${COVERAGE_TARGET_NAME}' with driver '${DRIVER}'")

    add_custom_target(${COVERAGE_TARGET_NAME} ;
      WORKING_DIRECTORY ${COVERAGE_OUTPUT_DIRECTORY}
      DEPENDS ${COVERAGE_DEPENDENCIES}
      )

    file(MAKE_DIRECTORY ${COVERAGE_OUTPUT_DIRECTORY})
  endif()

  add_dependencies("coverage" ${COVERAGE_TARGET_NAME})

  add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
    COMMAND ${LCOV_PATH} --directory .
                         --zerocounters
                         ${COVERAGE_QUIET_FLAG}
    COMMENT "${COVERAGE_COMMENT_PREFIX} Resetting coverage counters ..."
    )

  add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
    COMMAND ${ADD_COVERAGE_COMMAND} >/dev/null
    COMMENT "${COVERAGE_COMMENT_PREFIX} Running coverage driver ..."
    )

  add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
    COMMAND ${LCOV_PATH} --rc 'lcov_branch_coverage=1'
                         --directory .
                         --capture
                         --output-file ${COVERAGE_RAW_DATA}
                         ${COVERAGE_QUIET_FLAG}
    COMMENT "${COVERAGE_COMMENT_PREFIX} Collecting coverage data ..."
    )

  add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
    COMMAND ${LCOV_PATH} --rc 'lcov_branch_coverage=1'
                         --extract ${COVERAGE_RAW_DATA} ${EXTRACT_DIRECTORIES}
                         --output-file ${COVERAGE_CLEAN_DATA}
                         ${COVERAGE_QUIET_FLAG}
    COMMENT "${COVERAGE_COMMENT_PREFIX} Extracting project relevant data ..."
    )

  if(${COVERAGE_REPORT})
    find_program(GENHTML_PATH genhtml)
    if(NOT GENHTML_PATH)
      message(FATAL_ERROR "genhtml not found! Aborting...")
    endif()

    add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
      COMMAND ${GENHTML_PATH} --rc 'lcov_branch_coverage=1'
                              -o "${COVERAGE_REPORT_DIRECTORY}"
                              "${COVERAGE_CLEAN_DATA}"
                              "${COVERAGE_QUIET_FLAG}"
      COMMENT "${COVERAGE_COMMENT_PREFIX} Generating report ..."
      )

    add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
      COMMAND ;
      COMMENT "${COVERAGE_COMMENT_PREFIX} Report generated at: ${COVERAGE_REPORT_DIRECTORY}/index.html"
      )
  endif()

  add_custom_command(TARGET ${COVERAGE_TARGET_NAME} POST_BUILD
    COMMAND ${LCOV_PATH} --rc 'lcov_branch_coverage=1'
                         --summary ${COVERAGE_CLEAN_DATA}
    COMMENT "${COVERAGE_COMMENT_PREFIX} Summary:"
    )

endfunction()
