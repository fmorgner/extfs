cmake_minimum_required(VERSION 3.2)
project("extfs"
  LANGUAGES C CXX
  VERSION 1.0
  )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CXX_VERSION "c++1z")

include("CompilerSetup")
include("ConanPackages")

option(EXTFS_BUILD_STATIC "Build extfs as a static library" ON)
option(EXTFS_ENABLE_TESTS "Enable CUTE unit tests" ON)

add_subdirectory("external")

include_directories("include")
include_directories(SYSTEM "external/linenoise")
add_subdirectory("src")

if(${EXTFS_ENABLE_TESTS})
  include("CUTE")
  add_subdirectory("test")

  if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
    include("CodeCoverage")
    add_coverage(${PROJECT_NAME}
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test
      DEPENDENCIES ${CUTE_TARGETS}
      SOURCE_DIRECTORIES "${PROJECT_SOURCE_DIR}/src/fs/*"
      "${PROJECT_SOURCE_DIR}/include/fs/**.hpp"
      QUIET
      )
  endif()
endif()

