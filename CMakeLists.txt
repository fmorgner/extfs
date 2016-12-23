cmake_minimum_required(VERSION 3.2)
project("extfs" CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CXX_VERSION "c++1z")

include("CompilerSetup")
include("ConanPackages")

option(EXTFS_BUILD_STATIC "Build extfs as a static library" ON)

include_directories("include")
add_subdirectory("src")
