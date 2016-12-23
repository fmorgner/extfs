#ifndef EXTFS_SUPERBLOCK_HPP
#define EXTFS_SUPERBLOCK_HPP

#include <array>
#include <cstdint>

namespace fs::detail
  {

  using u32 = std::uint32_t;
  using s32 = std::int32_t;
  using u16 = std::uint16_t;
  using s16 = std::uint16_t;
  using u08 = std::uint8_t;

  template<std::size_t Size>
  using chr_arr = std::array<char, Size>;

  template<std::size_t Size>
  using u08_arr = std::array<u08, Size>;

  template<std::size_t Size>
  using u32_arr = std::array<u32, Size>;


  struct extfs_superblock
    {
    u32 const inodes_count{};
    u32 const blocks_count{};
    u32 const reserved_blocks_count{};
    u32 const free_blocks_count{};
    u32 const free_inodes_count{};
    u32 const first_data_block_id{};
    u32 const logical_block_size{};
    s32 const logical_fragment_size{};
    u32 const blocks_per_group{};
    u32 const fragments_per_group{};
    u32 const inodes_per_group{};
    u32 const last_mount_timestamp{};
    u32 const last_write_timestamp{};
    u16 const mount_count{};
    u16 const maximum_mount_count{};
    u16 const magic_number{};
    s16 const state{};
    s16 const error_behaviour{};
    s16 const revision_level_minor{};
    u32 const last_check_timestamp{};
    u32 const check_interval{};
    u32 const creator_operating_system_id{};
    u32 const revision_level{};
    u16 const super_user_id{};
    u16 const super_user_group_id{};
    u32 const first_inode_id{};
    u16 const inode_size{};
    u16 const superblock_group_id{};
    u32 const compatible_features{};
    u32 const incompatible_features{};
    u32 const read_only_compatible_features{};
    u08_arr<16> const uuid{};
    chr_arr<16> const volume_name{};
    chr_arr<64> const last_mount_point{};
    u32 const compression_algorithm{};
    u08 const file_preallocated_blocks_count{};
    u08 const directory_preallocated_blocks_count{};
    u16 const _padding{};
    u08_arr<16> const journal_superblock_uuid{};
    u32 const journal_inode_id{};
    u32 const journal_device_number{};
    u32 const last_orphan_inode_id{};
    u32_arr<4> const hash_seed{};
    u08 const hash_version{};
    u08_arr<3> const _reserved0{};
    u32 const default_mount_options{};
    u32 const first_meta_block_group_id{};
    u08_arr<760> const _reserved1{};
    };

  static_assert(sizeof(extfs_superblock) == 1024, "An ext* super block must have an exact size of 1024 byte!");

  }

#endif
