#ifndef EXTFS_SUPERBLOCK_HPP
#define EXTFS_SUPERBLOCK_HPP

#include "fs/detail/types.hpp"

#include <array>
#include <cstdint>

namespace fs::detail
  {

  /**
   * This structure describes the ext2/3/4 superblock
   *
   * @since 1.0
   */
  struct extfs_superblock
    {
    u32 const inodes_count{}; ///< The total number of inodes in the file system
    u32 const blocks_count{}; ///< The total number of blocks in the file system
    u32 const reserved_blocks_count{}; ///< The number of blocks reserved for the super user
    u32 const free_blocks_count{}; ///< The number of free blocks in the file system
    u32 const free_inodes_count{}; ///< The mumber of free inodes in the file system
    u32 const first_data_block_id{}; ///< The first block that carries user data in the file system
    u32 const logical_block_size{}; ///< The logical size of a block (1024 << logical_block_size)
    s32 const logical_fragment_size{}; ///< The logical size of a block (1024 << logical_fragment_size)
    u32 const blocks_per_group{}; ///< The number of blocks per block group
    u32 const fragments_per_group{}; ///< The number of fragments per block group
    u32 const inodes_per_group{}; ///< The number of inodes per block group
    u32 const last_mount_timestamp{}; ///< The unix timestamp when the file system was last mounted
    u32 const last_write_timestamp{}; ///< The unix timestamp of the last write operation to the file system
    u16 const mount_count{}; ///< The number of times the file system was mounted since the last check
    u16 const maximum_mount_count{}; ///< The maximum number of times the file system can be mounted until a full check
    u16 const magic_number{}; ///< The magic number identifying the file system type
    s16 const state{}; ///< The state of the file system
    s16 const error_behaviour{}; ///< The desired behaviour if a file system error occurs
    s16 const revision_level_minor{}; ///< The minor revision level of the file system
    u32 const last_check_timestamp{}; ///< The unix timestamp of the last check of the file system
    u32 const check_interval{}; ///< The unix time interval in which to check the file system
    u32 const creator_operating_system_id{}; ///< The operation system identifier of the OS that created the file system
    u32 const revision_level{}; ///< The revision level of the file system
    u16 const super_user_id{}; ///< The user ID of the super user
    u16 const super_user_group_id{}; ///< The group ID of the super user group
    u32 const first_inode_id{}; ///< The id of the first inode usable for standard files
    u16 const inode_size{}; ///< The size of an inode in bytes
    u16 const superblock_group_id{}; ///< The ID of the block group hosting this superblock
    u32 const compatible_features{}; ///< The active compatible features
    u32 const incompatible_features{}; ///< The active incompatible feature
    u32 const read_only_compatible_features{}; ///< The active features compatible with read-only mode
    u08_arr<16> const uuid{}; ///< The UUID of the file system
    chr_arr<16> const label{}; ///< The label of the file system
    chr_arr<64> const last_mount_point{}; ///< The location the file system was last mounted on
    u32 const compression_algorithm{}; ///< The compression algorithm used in the file system
    u08 const file_preallocated_blocks_count{}; ///< The number of blocks to preallocate for a file
    u08 const directory_preallocated_blocks_count{}; ///< The number of block to preallocate for a directory
    u16 const _padding{}; ///< Alignment padding
    u08_arr<16> const journal_superblock_uuid{}; ///< The UUID of the superblock containing the journal
    u32 const journal_inode_id{}; ///< The ID of the inode hosting the journal
    u32 const journal_device_number{}; ///< The device number of the journal
    u32 const last_orphan_inode_id{}; ///< The first inode in the list of inodes to delete
    u32_arr<4> const hash_seed{}; ///< The seed for the directory hashing algorithm
    u08 const hash_version{}; ///< The version of the directory hashing algorithm
    u08_arr<3> const _reserved0{}; ///< Alignment padding
    u32 const default_mount_options{}; ///< The default mount options for the file system
    u32 const first_meta_block_group_id{}; ///< The ID of the first meta block group
    u08_arr<760> const _reserved1{}; ///< Padding
    };

  static_assert(sizeof(extfs_superblock) == 1024, "An ext* super block must have an exact size of 1024 byte!");

  }

#endif
