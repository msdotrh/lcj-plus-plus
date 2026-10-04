#ifndef CLI_H
#define CLI_H
#include "file_handling/toml.hpp"
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

  void execute(TomlHandler &toml);
};

struct Remove {
  std::string name;

  void execute(TomlHandler &toml);
};

struct Reset {

  void execute(TomlHandler &toml);
};

struct Run {
  std::string name;
  std::optional<std::filesystem::path> input, output;
  std::optional<std::size_t> memory_limit;
  std::optional<std::chrono::milliseconds> time_limit;

  void execute(TomlHandler &toml);
};

struct Edit {
  std::string name;
  std::optional<std::filesystem::path> file, directory;
  std::optional<std::filesystem::path> input, output;
  std::optional<std::size_t> memory_limit;
  std::optional<std::chrono::milliseconds> time_limit;

  void execute(TomlHandler &toml);
};

struct List {
  void execute(TomlHandler &toml);
};
}; // namespace Command

void CLI_init(TomlHandler &toml);

#endif
