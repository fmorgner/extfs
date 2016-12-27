#include "fs/extfs.hpp"

#include "test/superblock/ext2-filetype.hpp"
#include "test/superblock/ext2-large_file.hpp"
#include "test/superblock/ext2-noopts.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ostream_listener.h>
#include <cute/xml_listener.h>

#include <cstring>

using cft = fs::detail::superblock::compatible_feature;
using ift = fs::detail::superblock::incompatible_feature;
using rft = fs::detail::superblock::read_only_compatible_feature;

auto superblock_from_bytes(std::array<std::uint8_t, 1024> const & data)
  {
  auto block = fs::detail::superblock{};
  std::memcpy(reinterpret_cast<char *>(&block), data.data(), data.size());
  return block;
  }

void default_initialized_superblock_should_have_no_compatible_features()
  {
  ASSERT(!fs::detail::superblock{}.has_any({
      cft::directory_preallocation,
      cft::imagic_inodes,
      cft::has_journal,
      cft::extended_attribues,
      cft::resize_inode,
      cft::directory_indexing,
      cft::lazy_block_group_initialization,
      cft::exclude_inode,
      cft::exclude_bitmaps,
      cft::sparse_superblock_v2,
      }));
  }

void default_initialized_superblock_should_have_no_incompatible_features()
  {
  ASSERT(!fs::detail::superblock{}.has_any({
      ift::compression,
      ift::filetype,
      ift::recover,
      ift::journal_device,
      ift::meta_block_group,
      ift::extents,
      ift::large_file_system,
      ift::multiple_mount_protection,
      ift::flexible_block_groups,
      ift::large_extended_attribues_in_inodes,
      ift::data_in_directories,
      ift::metadata_checksum_seed_in_superblock,
      ift::large_directory,
      ift::data_in_inode,
      ift::encrypted_inodes,
      }));
  }

void default_initialized_superblock_should_have_no_read_only_compatible_features()
  {
  ASSERT(!fs::detail::superblock{}.has_any({
      rft::sparse_superblock,
      rft::large_file,
      rft::binary_tree_directories,
      rft::huge_file,
      }));
  }

void noopts_superblock_should_have_no_opts()
  {
  auto block = superblock_from_bytes(ext2_noopts);
  ASSERT(!block.has_any({
      cft::directory_preallocation,
      cft::imagic_inodes,
      cft::has_journal,
      cft::extended_attribues,
      cft::resize_inode,
      cft::directory_indexing,
      cft::lazy_block_group_initialization,
      cft::exclude_inode,
      cft::exclude_bitmaps,
      cft::sparse_superblock_v2,
      }));

  ASSERT(!block.has_any({
      ift::compression,
      ift::filetype,
      ift::recover,
      ift::journal_device,
      ift::meta_block_group,
      ift::extents,
      ift::large_file_system,
      ift::multiple_mount_protection,
      ift::flexible_block_groups,
      ift::large_extended_attribues_in_inodes,
      ift::data_in_directories,
      ift::metadata_checksum_seed_in_superblock,
      ift::large_directory,
      ift::data_in_inode,
      ift::encrypted_inodes,
      }));

  ASSERT(!block.has_any({
      rft::sparse_superblock,
      rft::large_file,
      rft::binary_tree_directories,
      rft::huge_file,
      }));
  }

void filetype_superblock_should_have_filetype_option()
  {
  auto block = superblock_from_bytes(ext2_filetype);
  ASSERT(block.has(ift::filetype));
  }

void large_file_superblock_should_have_large_file_option()
  {
  auto block = superblock_from_bytes(ext2_large_file);
  ASSERT(block.has(rft::large_file));
  }

int main(int argc, char * argv[])
  {
  auto tests = cute::suite{
    CUTE(default_initialized_superblock_should_have_no_compatible_features),
    CUTE(default_initialized_superblock_should_have_no_incompatible_features),
    CUTE(default_initialized_superblock_should_have_no_read_only_compatible_features),
    CUTE(noopts_superblock_should_have_no_opts),
    CUTE(filetype_superblock_should_have_filetype_option),
    CUTE(large_file_superblock_should_have_large_file_option),
  };

  cute::xml_file_opener resultFile{argc, argv};
  cute::xml_listener<cute::ostream_listener<>> listener{resultFile.out};
  return !cute::makeRunner(listener, argc, argv)(tests, "fs::detail::superblock");
  }
