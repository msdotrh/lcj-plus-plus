#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct ioPair {
  std::filesystem::path input, output;
};

struct ProcessOutput {
  std::string standard_out, standard_err;
};

struct Process {
  std::string command;
  ProcessOutput output;
  std::vector<std::string> args;
  std::vector<ioPair> ioPairs;

  int Run();
};
