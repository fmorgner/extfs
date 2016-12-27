#ifndef EXTFS_SUPERBLOCK_HPP
#define EXTFS_SUPERBLOCK_HPP

#include "fs/detail/types.hpp"

#include <array>
#include <cstdint>
#include <initializer_list>
#include <type_traits>

namespace fs::detail
  {

  /**
   * This structure describes the ext2/3/4 superblock
   *
   * @since 1.0
   */
  struct superblock
    {
    /**
     * @brief The operating system that created the file system
     *
     * The "standard" utilities to create an ext2/3/4 file system record the operating system they were used on. The values of
     * this enumeration are the "well-known" operating systems, e.g the ones most implementations should understand.
     *
     * @since 1.0
     */
    enum struct creator_operating_system : u32
      {
      linux = 0, ///< Linux
      hurd = 1, ///<  HURD
      masix = 2, ///< MASIX
      freebsd = 3, ///< FreeBSD
      lites = 4, ///< Lites
      };

    /**
     * @brief The underlying type of #creator_operating_system
     *
     * @since 1.0
     */
    using cos = std::underlying_type_t<creator_operating_system>;

    /**
     * @brief The revision level of the file system
     *
     * ext2/3/4 currently come in two different revision levels, known as the "Good old" revision and the "Dynamic" revision.
     * The "Good old" format uses fixed inode size and generally lacks some "modern" features, whereas the "Dynamic" format
     * supports, among other things, dynamic inode sizes.
     *
     * @since 1.0
     */
    enum struct revision_level : u32
      {
      good_old = 0, ///< The first version of ext2
      dynamic = 1, ///< The file system supports "modern" features
      };

    /**
     * @brief The underlying type of #revision_level
     *
     * @since 1.0
     */
    using rlv = std::underlying_type_t<revision_level>;

    /**
     * @brief The compatible features of ext2/3/4
     *
     * ext2/3/4 define a set of so-called compatible features. Even if the implementation does not support these features, it
     * is safe to read and write data from and to the file system. The values of this enumeration reflect the currently
     * "well-known" features.
     *
     * @note The current implementation does not support any of the "compatible features".
     * @since 1.0
     */
    enum struct compatible_feature : u32
      {
      directory_preallocation = 1, ///< Blocks for new directories can be preallocated
      imagic_inodes = 2, ///< TODO: Find out what this does
      has_journal = 4, ///< The file system has an ext3 journal
      extended_attribues = 8, ///< The file system supports extended attributes
      resize_inode = 16, ///< The file system can be resized
      directory_indexing = 32, ///< The file system suppors directory indexing
      lazy_block_group_initialization = 64, ///< The file system lazily initializes block groups
      exclude_inode = 128, ///< TODO: Find out what that does
      exclude_bitmaps = 256, ///< The file system has snapshot-related exclude bitmaps
      sparse_superblock_v2 = 512, ///< The file system uses version 2 of the sparse superblock
      };

    /**
     * @brief The underlying type of compatible_feature
     *
     * @since 1.0
     */
    using cft = std::underlying_type_t<compatible_feature>;

    /**
     * @brief The incompatible features of ext2/3/4
     *
     * ext2/3/4 define a set of so-called incompatible features. If the file system makes use of one or more of these features
     * and the implementation does not support the features used, it must refuse to read or write from or to the file system.
     * The values of this enumeration are the currently "well-known" features.
     *
     * @note The current implementation implementation does not support any of the "incompatible features".
     * @since 1.0
     */
    enum struct incompatible_feature : u32
      {
      compression = 1, ///< The file system uses compression
      filetype = 2, ///< Filetypes are recorded in directory entries
      recover = 4, ///< The fFile system needs recovery
      journal_device = 8, ///< The file system has a separate device for the journal
      meta_block_group = 16, ///< The file system has meta block groups
      extents = 64, ///< The file system uses extents
      large_file_system = 128, ///< The file system supports 2^64 blocks
      multiple_mount_protection = 256, ///< The file system must be protected against being mounted more than once at a time
      flexible_block_groups = 512, ///< The file system uses flexible block groups
      large_extended_attribues_in_inodes = 1024, ///< The file system stores large extended attributes in inodes
      data_in_directories = 4096, ///< The file system stores data directly in directory entries
      metadata_checksum_seed_in_superblock = 8192, ///< The checksum seed for metadata is stored in the superblock
      large_directory = 16384, ///< The file system uses a large directory or 3-level hash tree
      data_in_inode = 32768, ///< The file system stores data directly inside inodes
      encrypted_inodes = 65536, ///< The file system uses encrypted inodes
      };

    /**
     * @brief The underlying type of incompatible_feature
     *
     * @since 1.0
     */
    using ift = std::underlying_type_t<incompatible_feature>;

    /**
     * @brief The read-only compatible features of ext2/3/4
     *
     * ext2/3/4 define a set of so-called read-only compatible features. An implementation that does not support one or more of
     * these features might still access the file system in a read-only way. The values of this enumeration are the currently
     * "well-known" read-only compatible features.
     *
     * @note The current implementation implementation does not support any of the "read-only compatible features".
     * @since 1.0
     */
    enum struct read_only_compatible_feature : u32
      {
      sparse_superblock = 1, ///< The file system has a sparse superblock
      large_file = 2, ///< The file system supports large files
      binary_tree_directories = 4, ///< The file system uses sorted binary trees for directories
      huge_file = 8, ///< The file system contains files represented by the number of logical blocks (e.g. HUGE files)
      };

    /**
     * @brief The underlying type of read_only_compatible_feature
     *
     * @since 1.0
     */
    using rft = std::underlying_type_t<read_only_compatible_feature>;

    /**
     * @brief The compression algorithms of ext2/3/4
     *
     * While compression in ext2 was only supported via a patch, later iterations added the compression feature as a "core"
     * component of the file system. The values of this enumeration are the currently "well-known" compression algorithms
     * found in ext2/3/4.
     *
     * @note The current implementation implementation does not support any of these algorithms.
     * @note A file system might be using multiple compression algorithms at a time.
     * @since 1.0
     */
    enum struct compression_algorithm : u32
      {
      lempel_ziv = 1, ///< Lempel-Ziv compression
      lempel_ziv_ross_williams_3a = 2, ///< Lempel-Ziv Ross-Williams 3A compression
      gzip = 4, ///< GZIP compression
      bzip2 = 8, ///< BZIP2 compression
      lempel_ziv_oberhumer = 16, ///< Lempel-Ziv-Oberhumer compression
      };

    /**
     * @brief The underlying type of compression_algorithms
     *
     * @since 1.0
     */
    using cpr = std::underlying_type_t<compression_algorithm>;

    u32 inodes_count{}; ///< The total number of inodes in the file system
    u32 blocks_count{}; ///< The total number of blocks in the file system
    u32 reserved_blocks_count{}; ///< The number of blocks reserved for the super user
    u32 free_blocks_count{}; ///< The number of free blocks in the file system
    u32 free_inodes_count{}; ///< The mumber of free inodes in the file system
    u32 first_data_block_id{}; ///< The first block that carries user data in the file system
    u32 logical_block_size{}; ///< The logical size of a block (1024 << logical_block_size)
    s32 logical_fragment_size{}; ///< The logical size of a block (1024 << logical_fragment_size)
    u32 blocks_per_group{}; ///< The number of blocks per block group
    u32 fragments_per_group{}; ///< The number of fragments per block group
    u32 inodes_per_group{}; ///< The number of inodes per block group
    u32 last_mount_timestamp{}; ///< The unix timestamp when the file system was last mounted
    u32 last_write_timestamp{}; ///< The unix timestamp of the last write operation to the file system
    u16 mount_count{}; ///< The number of times the file system was mounted since the last check
    u16 maximum_mount_count{}; ///< The maximum number of times the file system can be mounted until a full check
    u16 magic_number{}; ///< The magic number identifying the file system type
    s16 state{}; ///< The state of the file system
    s16 error_behaviour{}; ///< The desired behaviour if a file system error occurs
    s16 revision_level_minor{}; ///< The minor revision level of the file system
    u32 last_check_timestamp{}; ///< The unix timestamp of the last check of the file system
    u32 check_interval{}; ///< The unix time interval in which to check the file system
    cos creator_operating_system_id{}; ///< The operation system identifier of the OS that created the file system
    rlv revision_level{}; ///< The revision level of the file system
    u16 super_user_id{}; ///< The user ID of the super user
    u16 super_user_group_id{}; ///< The group ID of the super user group
    u32 first_inode_id{}; ///< The id of the first inode usable for standard files
    u16 inode_size{}; ///< The size of an inode in bytes
    u16 superblock_group_id{}; ///< The ID of the block group hosting this superblock
    cft compatible_features_bitmap{}; ///< The active compatible features
    ift incompatible_features_bitmap{}; ///< The active incompatible feature
    rft read_only_compatible_features_bitmap{}; ///< The active features compatible with read-only mode
    u08_arr<16> uuid{}; ///< The UUID of the file system
    chr_arr<16> label{}; ///< The label of the file system
    chr_arr<64> last_mount_point{}; ///< The location the file system was last mounted on
    cpr compression_algorithms_bitmap{}; ///< The compression algorithms used in the file system
    u08 file_preallocated_blocks_count{}; ///< The number of blocks to preallocate for a file
    u08 directory_preallocated_blocks_count{}; ///< The number of block to preallocate for a directory
    u16 _padding{}; ///< Alignment padding
    u08_arr<16> journal_superblock_uuid{}; ///< The UUID of the superblock containing the journal
    u32 journal_inode_id{}; ///< The ID of the inode hosting the journal
    u32 journal_device_number{}; ///< The device number of the journal
    u32 last_orphan_inode_id{}; ///< The first inode in the list of inodes to delete
    u32_arr<4> hash_seed{}; ///< The seed for the directory hashing algorithm
    u08 hash_version{}; ///< The version of the directory hashing algorithm
    u08_arr<3> _reserved0{}; ///< Alignment padding
    u32 default_mount_options{}; ///< The default mount options for the file system
    u32 first_meta_block_group_id{}; ///< The ID of the first meta block group
    u08_arr<760> _reserved1{}; ///< Padding

    /**
     * @brief Check if the file system has the desired "compatible feature"
     *
     * @param feature The #compatible_feature to check for
     * @return @p true iff. the file system has the feature, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has(compatible_feature const feature) const;

    /**
     * @brief Check if the file system has all of the desired "compatible features"
     *
     * @param features The @link compatible_feature compatible_features to check for
     * @return @p true iff. the file system has @a all features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_all(std::initializer_list<compatible_feature> const features) const;

    /**
     * @brief Check if the file system has at least one of the desired "compatible features"
     *
     * @param features The @link compatible_feature compatible_features to check for
     * @return @p true iff. the file system has @a at least one of the features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_any(std::initializer_list<compatible_feature> const features) const;

    /**
     * @brief Check if the file system has the desired "incompatible feature"
     *
     * @param feature The #incompatible_feature to check for.
     * @return @p true iff. the file system has the feature
     * @see #incompatible_feature
     * @since 1.0
     */
    bool has(incompatible_feature const feature) const;

    /**
     * @brief Check if the file system has all of the desired "incompatible features"
     *
     * @param features The @link incompatible_feature incompatible_features to check for
     * @return @p true iff. the file system has @a all features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_all(std::initializer_list<incompatible_feature> const features) const;

    /**
     * @brief Check if the file system has at least one of the desired "incompatible features"
     *
     * @param features The @link incompatible_feature incompatible_features to check for
     * @return @p true iff. the file system has @a at least one of the features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_any(std::initializer_list<incompatible_feature> const features) const;

    /**
     * @brief Check if the file system has the desired "read-only compatible feature"
     *
     * @param feature The #read_only_compatible_feature to check for
     * @return @p true iff. the file system has the feature, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has(read_only_compatible_feature const feature) const;

    /**
     * @brief Check if the file system has all of the desired "read-only compatible features"
     *
     * @param features The @link read_only_compatible_feature read_only_compatible_features to check for
     * @return @p true iff. the file system has @a all features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_all(std::initializer_list<read_only_compatible_feature> const features) const;

    /**
     * @brief Check if the file system has at least one of the desired "read-only compatible features"
     *
     * @param features The @link read_only_compatible_feature read_only_compatible_features to check for
     * @return @p true iff. the file system has @a at least one of the features that were querried, @p false otherwise
     * @see #compatible_feature
     * @since 1.0
     */
    bool has_any(std::initializer_list<read_only_compatible_feature> const features) const;

    };

  static_assert(sizeof(superblock) == 1024, "An ext2/3/4 super block must have an exact size of 1024 bytes!");

  }

#endif
