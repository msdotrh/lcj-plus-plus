#ifndef CLI_H
#define CLI_H
#pragma once

#include <chrono>
#include <filesystem>
#include <optional>
#include <string>

namespace Command {
struct Add {
  std::string name;
  std::filesystem::path file, directory;
  std::optional<std::filesystem::path> input, output;
  std::optional<std::size_t> memory_limit;
  std::optional<std::chrono::milliseconds> time_limit;

  void execute();
};

struct Remove {
  std::string name;

  void execute();
};

struct Reset {

  void execute();
};

struct Run {
  std::string name;
  std::optional<std::filesystem::path> input, output;
  std::optional<std::size_t> memory_limit;
  std::optional<std::chrono::milliseconds> time_limit;

  void execute();
};

struct Edit {
  std::string name;
  std::filesystem::path file, directory;
  std::optional<std::filesystem::path> input, output;
  std::optional<std::size_t> memory_limit;
  std::optional<std::chrono::milliseconds> time_limit;

  void execute();
};

struct List {
  void execute();
};
};


void CLI_init();

#endif
