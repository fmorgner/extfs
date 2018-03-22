add_subdirectory(fs)

add_executable(extsh
  extsh.cpp
  $<TARGET_OBJECTS:linenoise>
  )
target_link_libraries(extsh
  extfs
  )
