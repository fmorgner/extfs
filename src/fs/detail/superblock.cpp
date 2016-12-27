#include "fs/detail/superblock.hpp"

#include <algorithm>

namespace fs::detail
  {

  bool superblock::has(superblock::compatible_feature const feature) const
    {
    return compatible_features_bitmap & static_cast<decltype(compatible_features_bitmap)>(feature);
    }

  bool superblock::has_all(std::initializer_list<superblock::compatible_feature> const features) const
    {
    return std::all_of(features.begin(), features.end(), [&](auto const feature){
      return compatible_features_bitmap & static_cast<decltype(compatible_features_bitmap)>(feature);
    });
    }

  bool superblock::has_any(std::initializer_list<superblock::compatible_feature> const features) const
    {
    return std::any_of(features.begin(), features.end(), [&](auto const feature){
      return compatible_features_bitmap & static_cast<decltype(compatible_features_bitmap)>(feature);
    });
    }

  bool superblock::has(superblock::incompatible_feature const feature) const
    {
    return incompatible_features_bitmap & static_cast<decltype(incompatible_features_bitmap)>(feature);
    }

  bool superblock::has_all(std::initializer_list<superblock::incompatible_feature> const features) const
    {
    return std::all_of(features.begin(), features.end(), [&](auto const feature){
      return incompatible_features_bitmap & static_cast<decltype(incompatible_features_bitmap)>(feature);
    });
    }

  bool superblock::has_any(std::initializer_list<superblock::incompatible_feature> const features) const
    {
    return std::any_of(features.begin(), features.end(), [&](auto const feature){
      return incompatible_features_bitmap & static_cast<decltype(incompatible_features_bitmap)>(feature);
    });
    }

  bool superblock::has(superblock::read_only_compatible_feature const feature) const
    {
    return read_only_compatible_features_bitmap & static_cast<decltype(read_only_compatible_features_bitmap)>(feature);
    }

  bool superblock::has_all(std::initializer_list<superblock::read_only_compatible_feature> const features) const
    {
    return std::all_of(features.begin(), features.end(), [&](auto const feature){
      return read_only_compatible_features_bitmap & static_cast<decltype(read_only_compatible_features_bitmap)>(feature);
    });
    }

  bool superblock::has_any(std::initializer_list<superblock::read_only_compatible_feature> const features) const
    {
    return std::any_of(features.begin(), features.end(), [&](auto const feature){
      return read_only_compatible_features_bitmap & static_cast<decltype(read_only_compatible_features_bitmap)>(feature);
    });
    }

  }
