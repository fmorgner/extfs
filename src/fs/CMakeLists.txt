if(EXTFS_BUILD_STATIC)
  set(LIBRARY_TYPE "STATIC")
else()
  set(LIBRARY_TYPE "SHARED")
endif()

add_library(extfs
  ${LIBRARY_TYPE}
  extfs.cpp
  )
