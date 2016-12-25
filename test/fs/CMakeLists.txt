set(CUTE_GROUP "fs")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/test/extfs_data")
message(STATUS "Creating test disk images")
execute_process(
  COMMAND dd if=/dev/urandom of=${CMAKE_BINARY_DIR}/test/extfs_data/labeled.img bs=1M count=1
  OUTPUT_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_labeled_dd.stdout.log
  ERROR_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_labeled_dd.stderr.log
  )
execute_process(
  COMMAND mkfs.ext2 -F -L labeleddisk ${CMAKE_BINARY_DIR}/test/extfs_data/labeled.img
  OUTPUT_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_labeled_mkfs.stdout.log
  ERROR_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_labeled_mkfs.stderr.log
  )
execute_process(
  COMMAND dd if=/dev/urandom of=${CMAKE_BINARY_DIR}/test/extfs_data/unlabeled.img bs=1M count=1
  OUTPUT_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_unlabeled_dd.stdout.log
  ERROR_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_unlabeled_dd.stderr.log
  )
execute_process(
  COMMAND mkfs.ext2 -F ${CMAKE_BINARY_DIR}/test/extfs_data/unlabeled.img
  OUTPUT_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_unlabeled_mkfs.stdout.log
  ERROR_FILE ${CMAKE_BINARY_DIR}/extfs_vdisk_unlabeled_mkfs.stderr.log
  )

cute_test(extfs LIBRARIES extfs stdc++fs)
