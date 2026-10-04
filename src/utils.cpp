#include "utils.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <print>
#include <toml++/impl/array.hpp>

void utils::create_file(const std::filesystem::path &path) {
  const auto parent = path.parent_path();

  if (!parent.empty()) {
    std::filesystem::create_directories(parent);
  }

  std::ofstream file;
  file.open(path, std::ios::out | std::ios::trunc);
  if (!file.is_open()) {
    std::println(stderr, "Can not create / or reset file at path: {}",
                 path.string());
    std::terminate();
  }

  file.close();
}
