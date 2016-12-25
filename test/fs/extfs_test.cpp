#include "fs/extfs.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ostream_listener.h>
#include <cute/xml_listener.h>

#if __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace stdfs = std::experimental::filesystem;
#elif __has_include(<filesystem>)
#include <filesystem>
namespace stdfs = std::filesystem;
#else
#error The standard library has no support for the Filesystem TS
#endif

#include <initializer_list>
#include <stdexcept>
#include <string>

auto constexpr kNonExistantImage = "THIS_DISK_DOES_NOT_EXIST";
auto constexpr kLabeledDiskImage = "../test/extfs_data/labeled.img";
auto constexpr kUnlabeledDiskImage = "../test/extfs_data/unlabeled.img";

bool disk_exists(stdfs::path const & imagePath)
  {
  return stdfs::exists(imagePath) && stdfs::is_regular_file(imagePath);
  }

auto guard_disk_image_any(std::initializer_list<char const *> imageList,
                          fs::extfs::mode const mode = fs::extfs::mode::read_only)
  {
  ASSERT_GREATER_EQUALM("imageList must not be emtpy!", imageList.size(), 0);

  for(auto && path : imageList)
    {
    if(disk_exists(path))
      {
      return fs::extfs(path, mode);
      }
    }

  throw std::runtime_error{"None of the expected disk images could be found!"};
  }

auto guard_disk_image_none(std::initializer_list<char const *> imageList)
  {
  ASSERT_GREATER_EQUALM("imageList must not be emtpy!", imageList.size(), 0);

  for(auto && path : imageList)
    {
    if(disk_exists(path))
      {
      throw std::runtime_error{"Found unexpected disk image!"};
      }
    }

  return fs::extfs{*imageList.begin()};
  }

void construction_with_inexistent_file_creates_extfs_that_is_not_open()
  {
  auto && disk = guard_disk_image_none({kNonExistantImage});
  ASSERT(!disk.open());
  }

void non_open_file_system_has_no_label()
  {
  auto && disk = guard_disk_image_none({kNonExistantImage});
  ASSERT(!disk.has_label());
  }

void non_open_file_system_has_empty_label()
  {
  auto && disk = guard_disk_image_none({kNonExistantImage});
  ASSERT_EQUAL("", disk.label());
  }

void construction_with_existing_file_creates_extfs_that_is_open()
  {
  auto && disk = guard_disk_image_any({kLabeledDiskImage, kUnlabeledDiskImage});
  ASSERT(disk.open());
  }

void construction_with_labeled_image_creates_extfs_that_has_label()
  {
  auto && disk = guard_disk_image_any({kLabeledDiskImage});
  ASSERT(disk.has_label());
  }

void construction_with_unlabeled_image_creates_extfs_that_has_no_label()
  {
  auto && disk = guard_disk_image_any({kUnlabeledDiskImage});
  ASSERT(!disk.has_label());
  }

void construction_with_labeled_image_creates_extfs_that_has_label_labeleddisk()
  {
  auto && disk = guard_disk_image_any({kLabeledDiskImage});
  ASSERT_EQUAL("labeleddisk", disk.label());
  }

void construction_with_unlabeled_image_creates_extfs_that_has_empty_string_for_label()
  {
  auto && disk = guard_disk_image_any({kUnlabeledDiskImage});
  ASSERT_EQUAL("", disk.label());
  }

int main(int argc, char * argv[])
  {
  auto tests = cute::suite{
    CUTE(construction_with_inexistent_file_creates_extfs_that_is_not_open),
    CUTE(non_open_file_system_has_no_label),
    CUTE(non_open_file_system_has_empty_label),
    CUTE(construction_with_existing_file_creates_extfs_that_is_open),
    CUTE(construction_with_labeled_image_creates_extfs_that_has_label),
    CUTE(construction_with_unlabeled_image_creates_extfs_that_has_no_label),
    CUTE(construction_with_labeled_image_creates_extfs_that_has_label_labeleddisk),
    CUTE(construction_with_unlabeled_image_creates_extfs_that_has_empty_string_for_label),
  };

  cute::xml_file_opener resultFile{argc, argv};
  cute::xml_listener<cute::ostream_listener<>> listener{resultFile.out};
  return !cute::makeRunner(listener, argc, argv)(tests, "fs::extfs tests");
  }
