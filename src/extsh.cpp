#include "fs/extfs.hpp"

#include <iostream>
#include <string>

int main(int argc, char const * argv[])
  {
  auto const & path = [&]{ return std::string{argc > 1 ? argv[1] : "vdisk.img"}; }();
  auto const & disk = fs::extfs{path};

  if(disk)
    {
    std::clog << "[EXT2] Successfully opened ext*fs at: '" << path << "'\n";
    }
  else
    {
    std::clog << "[EXT2] Failed to open ext*fs at: '" << path << "'\n";
    }
  }
