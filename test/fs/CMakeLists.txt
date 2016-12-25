set(CUTE_GROUP "fs")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/test/extfs_data")
message(STATUS "Creating test disk images")
execute_process(
  COMMAND dd if=/dev/zero of=${CMAKE_BINARY_DIR}/test/extfs_data/labeled.img bs=1M count=1
  OUTPUT_QUIET
  ERROR_QUIET
  )
execute_process(
  COMMAND mkfs.ext2 -L labeleddisk ${CMAKE_BINARY_DIR}/test/extfs_data/labeled.img
  OUTPUT_QUIET
  ERROR_QUIET
  )
execute_process(
  COMMAND dd if=/dev/zero of=${CMAKE_BINARY_DIR}/test/extfs_data/unlabeled.img bs=1M count=1
  OUTPUT_QUIET
  ERROR_QUIET
  )
execute_process(
  COMMAND mkfs.ext2 ${CMAKE_BINARY_DIR}/test/extfs_data/unlabeled.img
  OUTPUT_QUIET
  ERROR_QUIET
  )

cute_test(extfs LIBRARIES extfs stdc++fs)
