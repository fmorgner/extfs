if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt")
  message(STATUS "Current conanfile.txt directory: ${CMAKE_CURRENT_SOURCE_DIR}")
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    message(STATUS "Collecting conan packages")
    execute_process(
      COMMAND
      conan install --build=missing --generator cmake ${CMAKE_CURRENT_SOURCE_DIR}
      OUTPUT_QUIET
      )
  endif()
else()
  message(FATAL_ERROR "No conanfile found at '${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt'")
endif()

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")

set(CONAN_SYSTEM_INCLUDES ON)
conan_check_compiler()
conan_flags_setup()
conan_set_find_paths()
