#ifndef EXTFS_EXTFS_HPP
#define EXTFS_EXTFS_HPP

#include "fs/detail/superblock.hpp"

#include <fstream>
#include <string>

namespace fs
  {

  struct extfs
    {
    enum struct mode : char
      {
      read_only,
      writeable
      };

    /**
     * Open the filesystem at a given path
     *
     * @param path The path to a device/file containing an ext* file system.
     * @param openMode Whether to open the file system in read_only or writeable mode.
     * @since 1.0
     */
    explicit extfs(std::string const & path, mode const openMode = mode::read_only);

    /**
     * Check if the filesystem is valid
     */
    operator bool() const;

    private:
      std::fstream m_stream{};
      detail::extfs_superblock m_primarySuperblock{};
    };

  }

#endif
