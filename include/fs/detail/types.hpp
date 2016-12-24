#ifndef EXTFS_TYPES_HPP
#define EXTFS_TYPES_HPP

#include <array>
#include <cstdint>

namespace fs::detail
  {

  using u32 = std::uint32_t; ///< An unsigned 32-bit integer
  using s32 = std::int32_t; ///< A signed 32-bit integer
  using u16 = std::uint16_t; ///< An unsigned 16-bit integer
  using s16 = std::uint16_t; ///< A signed 16-bit integer
  using u08 = std::uint8_t; ///< An unsigned 8-bit integer

  /**
   * An array of characters
   *
   * @tparam Size The size of the array
   */
  template<std::size_t Size>
  using chr_arr = std::array<char, Size>;

  /**
   * An array of unsigned 8-bit integers
   *
   * @tparam Size The size of the array
   */
  template<std::size_t Size>
  using u08_arr = std::array<u08, Size>;

  /**
   * An array of unsigned 32-bit integers
   *
   * @tparam Size The size of the array
   */
  template<std::size_t Size>
  using u32_arr = std::array<u32, Size>;

  }

#endif
