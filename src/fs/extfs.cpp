#include "fs/detail/superblock.hpp"
#include "fs/extfs.hpp"

#include <fstream>
#include <string>

namespace
  {
  auto constexpr kPrimarySuperblockLocation = 1024;
  auto constexpr kExtfsMagic = 0xef53;

  auto read_superblock(std::fstream & stream, fs::detail::extfs_superblock & superblock)
    {
    auto const originalPosition = stream.tellg();
    stream.seekg(kPrimarySuperblockLocation);
    stream.read(reinterpret_cast<char *>(&superblock), sizeof(fs::detail::extfs_superblock));
    stream.seekg(originalPosition);
    }
  }

namespace fs
  {

  extfs::extfs(std::string const & path, extfs::mode const openMode) :
    m_stream{path, std::ios::binary | (openMode == mode::read_only ? std::ios::in : std::ios::in | std::ios::out)}
    {
    read_superblock(m_stream, m_primarySuperblock);
    }

  extfs::operator bool() const
    {
    return m_stream && m_primarySuperblock.magic_number == kExtfsMagic;
    }

  }
