#include "fs/extfs.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ostream_listener.h>
#include <cute/xml_listener.h>

void construction_with_inexistent_file_creates_extfs_that_is_not_open()
  {
  auto && disk = fs::extfs{"./THIS_DISK_DOES_NOT_EXIST"};
  ASSERT(!disk.open());
  }

void non_open_file_system_has_no_label()
  {
  auto && disk = fs::extfs{"./THIS_DISK_DOES_NOT_EXIST"};
  ASSERT(!disk.has_label());
  }

int main(int argc, char * argv[])
  {
  auto tests = cute::suite{
    CUTE(construction_with_inexistent_file_creates_extfs_that_is_not_open),
    CUTE(non_open_file_system_has_no_label),
  };

  cute::xml_file_opener resultFile{argc, argv};
  cute::xml_listener<cute::ostream_listener<>> listener{resultFile.out};
  return !cute::makeRunner(listener, argc, argv)(tests, "fs::extfs tests");
  }
