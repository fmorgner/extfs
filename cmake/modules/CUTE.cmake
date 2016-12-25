#[============================================================================[.rst:
CUTE
----

CUTE (C++ Unit Testing Easier) integration for CMake

This module provides a function to easily add CUTE based unit tests to cmake
based C++ projects. Additionally, this module handles the activation of
cmake's underlying testing infrastructure to cleanly integrate CUTE tests
with ctest.

.. command: cute_test

  Add a CUTE test to the project::

    cute_test(<TestName>
      [GROUP <groupname>]
      [DEPENDENCIES <compiliation_dependency>...]
      [LIBRARIES <linking_dependency>...]
      [UNIQUE (On|Off)]
      [RUN_DURING_BUILD (On|Off)]
      )

  This function will search for one of the following files:

    - <TestName>.cpp
    - <TestName>.cxx
    - <TestName>.cc

  If none OR multiple files are found, a fatal error will be raised.

  The options for the function are:

  ``GROUP <groupname>``
    Add the test to the test-group named ``<groupname>``. Grouping tests adds
    another target to enable to run a specified test group only. The default
    for this value is the project name.

  ``DEPENDENCIES <compiliation_dependency>...``
    Add compile-time dependencies to the test. ``<compiliation_dependency>``
    shall be either a file name or a
    :manual:`generator expression <cmake-generator-expressions(7)>`. If one
    or more of the file names provided can not be resolved to actual files,
    test addition will fail.

  ``LIBRARIES <linking_dependency>...``
    Add link-time dependencies to the test. Every expression that is valid for
    use in ``target_link_libraries`` is also valid as an expression for
    ``linking_dependency``.

  ``UNIQUE (On|Off)``
    If enabled, ``cute_test`` will try to ensure the uniqueness of the tests
    name by appending part of a SHA256 hash of the tests group name. The
    default for this parameter is ``On``.

    ``RUN_DURING_BUILD (On|Off)``
    If enable, the test will be run as part of the build process. The default
    is On.

#]============================================================================]

# Include CMake's argument parsing module
include(CMakeParseArguments)

# Enable generation of testing targets
enable_testing()

# Set the output path for CUTE test reports and create it
set(${PROJECT_NAME}_CUTE_REPORTS_DIRECTORY
  ${PROJECT_BINARY_DIR}/cute-reports
  CACHE
  STRING
  "Output directory for CUTE test reports of ${PROJECT_NAME}"
  )
file(MAKE_DIRECTORY ${${PROJECT_NAME}_CUTE_REPORTS_DIRECTORY})

function(cute_test TEST_NAME)
  # Setup and parse arguments
  set(OPTIONS)
  set(SV_ARGUMENTS GROUP UNIQUE RUN_DURING_BUILD)
  set(MV_ARGUMENTS DEPENDENCIES LIBRARIES)
  cmake_parse_arguments(CUTE_TEST "${OPTIONS}" "${SV_ARGUMENTS}" "${MV_ARGUMENTS}" ${ARGN})

  # Use ``CUTE_UNIQUE`` as fallback, otherwise default to On for CUTE_TEST_ENSURE_UNIQUE
  if(NOT DEFINED CUTE_TEST_UNIQUE)
    if(DEFINED CUTE_UNIQUE)
      set(CUTE_TEST_UNIQUE ${CUTE_UNIQUE})
    else()
      set(CUTE_TEST_UNIQUE On)
    endif()
  endif()

  # Use ``CUTE_GROUP`` as fallback, otherwise default to ``PROJECT_NAME`` for CUTE_TEST_GROUP
  if(NOT DEFINED CUTE_TEST_GROUP)
    if(DEFINED CUTE_GROUP)
      set(TEST_TARGET_GROUP ${CUTE_GROUP})
      set(CUTE_TEST_GROUP "${PROJECT_NAME}::${CUTE_GROUP}")
    else()
      set(CUTE_TEST_GROUP "${PROJECT_NAME}")
    endif()
  else()
    set(TEST_TARGET_GROUP ${CUTE_TEST_GROUP})
    set(CUTE_TEST_GROUP "${PROJECT_NAME}::${CUTE_TEST_GROUP}")
  endif()
  string(REGEX REPLACE "::" "_" TEST_TARGET_GROUP ${CUTE_TEST_GROUP})

  # Use ``CUTE_RUN_DURING_BUILD`` as fallback, otherwise default to On for CUTE_TEST_RUN_DURIN_BUILD
  if(NOT DEFINED CUTE_TEST_RUN_DURING_BUILD)
    if(DEFINED CUTE_RUN_DURING_BUILD)
      set(CUTE_TEST_RUN_DURING_BUILD ${CUTE_RUN_DURING_BUILD})
    else()
      set(CUTE_TEST_RUN_DURING_BUILD On)
    endif()
  endif()


  # Set the output path for the CUTE test binaries
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cute-tests/${TEST_TARGET_GROUP}")

  # Search for the source file associated with this test. Fail if the number of found files
  # is anything else than 1.
  set(SOURCE_FILE_CANDIDATES ${TEST_NAME}_test.cpp ${TEST_NAME}_test.cxx ${TEST_NAME}_test.cc)
  set(CANDIDATE_COUNT 0)
  foreach(CANDIDATE IN LISTS SOURCE_FILE_CANDIDATES)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${CANDIDATE})
      MATH(EXPR CANDIDATE_COUNT "${CANDIDATE_COUNT}+1")
      set(TEST_SOURCE_FILE ${CANDIDATE})
    endif()
  endforeach()
  if(CANDIDATE_COUNT GREATER 1)
    message(FATAL_ERROR "More than one source candidate for ${TEST_NAME}")
  elseif(CANDIDATE_COUNT LESS 1)
    message(FATAL_ERROR "No source candidate for ${TEST_NAME}")
  endif()

  # If enabled, generate a unique name for the test
  if(${CUTE_TEST_UNIQUE})
    string(SHA256 GROUP_HASH ${CUTE_TEST_GROUP})
    string(SUBSTRING ${GROUP_HASH} 0 8 GROUP_HASH)
    set(TEST_NAME "${TEST_NAME}_${GROUP_HASH}")
  endif()

  # Build the target name for the test
  if(${TEST_TARGET_GROUP})
    set(TEST_TARGET_NAME "${TEST_TARGET_GROUP}_${TEST_NAME}_test")
  else()
    set(TEST_TARGET_NAME "${TEST_NAME}_test")
  endif()

  if(NOT TARGET ${TEST_TARGET_NAME})
    # Register the test with CMake
    message(STATUS "Registering CUTE test '${CUTE_TEST_GROUP}::${TEST_NAME}'")
    add_executable(${TEST_TARGET_NAME} ${TEST_SOURCE_FILE} ${CUTE_TEST_DEPENDENCIES})
    target_link_libraries(${TEST_TARGET_NAME} ${CUTE_TEST_LIBRARIES})
    add_test(NAME ${TEST_TARGET_NAME} WORKING_DIRECTORY ${${PROJECT_NAME}_CUTE_REPORTS_DIRECTORY} COMMAND ${TEST_TARGET_NAME})
    list(APPEND CUTE_TARGETS ${TEST_TARGET_NAME})
    set(CUTE_TARGETS ${CUTE_TARGETS} CACHE INTERNAL "All CUTE targets" FORCE)

    # Run tests during compilations if enabled
    if(${CUTE_TEST_RUN_DURING_BUILD})
      add_custom_target(cute_${TEST_TARGET_NAME} ALL
        COMMAND ctest -R ${TEST_TARGET_NAME} -Q --output-on-failure
        DEPENDS ${TEST_TARGET_NAME}
        COMMENT "Running CUTE test '${CUTE_TEST_GROUP}::${TEST_NAME}' ..."
        VERBATIM)
    endif()

    # Add a group target
    if(NOT ${TEST_TARGET_GROUP} STREQUAL "")
      set(GROUP_TARGET "test_${TEST_TARGET_GROUP}")
      if(NOT TARGET ${GROUP_TARGET})
        add_custom_target(${GROUP_TARGET}
          COMMAND ctest -R ${TEST_TARGET_GROUP}* -Q ---output-on-failure
          DEPENDS ${TEST_TARGET_NAME}
          COMMENT "Running tests in group '${CUTE_TEST_GROUP}' ..."
          VERBATIM)
      else()
        add_dependencies(${GROUP_TARGET} ${TEST_TARGET_NAME})
      endif()
    endif()
  endif()
endfunction()
