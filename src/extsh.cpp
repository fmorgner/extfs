#include "fs/extfs.hpp"

#include <iostream>
#include <string>

int main(int argc, char const * argv[])
  {
  auto const & path = [&]{ return std::string{argc > 1 ? argv[1] : "vdisk.img"}; }();
  auto const & disk = fs::extfs{path};

  if(disk.open())
    {
    std::clog << "[EXTSH] Successfully opened ext*fs at: '" << path << "'\n";
    if(disk.has_label())
      {
      std::clog << "[EXTSH] The filesystem is labeled '" << disk.label() << "'\n";
      }
    }
  else
    {
    std::clog << "[EXTSH] Failed to open ext*fs at: '" << path << "'\n";
    }
  }
