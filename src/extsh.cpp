#include "fs/extfs.hpp"

#include <linenoise.h>

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

enum struct result : std::uint8_t
  {
  keep_going,
  fatal_error,
  exit,
  unknown,
  };

result process(std::string const & command)
  {
  if(command == "exit" || command.empty())
    {
    return result::exit;
    }

  return result::unknown;
  }

std::string prompt(fs::extfs const & disk)
  {
  using namespace std::string_literals;

  auto const promptText = "["s + (disk.has_label() ? disk.label() : "No Label") + "] > ";
  auto const input = linenoise(promptText.c_str());
  if(input)
    {
    linenoiseHistoryAdd(input);
    auto const inputString = std::string{input};
    linenoiseFree(input);
    return inputString;
    }

  return {};
  }

void repl(fs::extfs & disk)
  {
  result commandResult = result::unknown;
  while((commandResult = process(prompt(disk))) != result::exit)
    {
    switch(commandResult)
      {
      case result::unknown:
        std::cout << "unknown command\n";
        break;
      case result::fatal_error:
        std::cout << "fatal error\n";
        return;
      default:
        break;
      }
    }

  std::cout << "Bye!\n";
  }

int main(int argc, char const * argv[])
  {
  auto const & path = [&]{ return std::string{argc > 1 ? argv[1] : "vdisk.img"}; }();
  fs::extfs disk{path};

  if(disk.open())
    {
    linenoiseHistorySetMaxLen(1024);
    repl(disk);
    }
  else
    {
    std::clog << "Failed to open ext*fs at: '" << path << "'\n";
    }
  }
