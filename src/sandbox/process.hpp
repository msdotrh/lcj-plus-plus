#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct ioPair {
  std::filesystem::path input, output;
};

struct Process {
  std::string command;
  std::string output;
  std::vector<std::string> args;
  std::vector<ioPair> ioPairs;

  int status_code;
  void Run();
};
