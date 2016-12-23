add_subdirectory(fs)

add_executable(extsh
  extsh.cpp
  )
target_link_libraries(extsh
  extfs
  )
