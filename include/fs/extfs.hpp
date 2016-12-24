#ifndef EXTFS_EXTFS_HPP
#define EXTFS_EXTFS_HPP

#include "fs/detail/superblock.hpp"

#include <fstream>
#include <string>

namespace fs
  {

  /**
   * @brief The ext* file system
   *
   * This abstraction provides a top-level interface to an ext* family file system. It grants access to information like the
   * size of the file system, the space left on the file system as well as the label.
   *
   * @since 1.0
   */
  struct extfs
    {
    /**
     * @brief How to open the file system
     *
     * @since 1.0
     */
    enum struct mode : char
      {
      read_only, ///< Open in read-only mode
      writeable, ///< Open in read-write mode
      };

    /**
     * @brief Open the filesystem at a given path
     *
     * @param path The path to a device/file containing an ext* file system.
     * @param openMode Whether to open the file system in read_only or writeable mode.
     *
     * @since 1.0
     *
     * @note This call will also succeed if the file system could not be opened for some reason. To check whether the file
     * system was successfully opened, see #fs::extfs::open().
     */
    explicit extfs(std::string const & path, mode const openMode = mode::read_only);

    /**
     * @brief Check if the filesystem is open.
     *
     * @return @p true, iff. the file system is opened, @p false otherwise
     *
     * @since 1.0
     */
    bool open() const;

    private:
      std::fstream m_stream{};
      detail::extfs_superblock m_primarySuperblock{};
    };

  }

#endif
