#include "utils.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <print>

void utils::create_file(const std::filesystem::path &path) {
  const auto parent = path.parent_path();

  if (!parent.empty()) {
    std::filesystem::create_directories(parent);
  }

  std::ofstream file;
  file.open(path);
  if (!file.is_open()) {
    std::println(stderr, "Can not create file: {}", path.string());
    std::terminate();
  }

  file.close();
}