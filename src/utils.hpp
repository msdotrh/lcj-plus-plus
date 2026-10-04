#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <toml++/toml.hpp>

namespace utils {

inline bool is_ascii(const std::string &s) {
  return std::ranges::all_of(s, [](unsigned char c) { return c < 128; });
}

void create_file(const std::filesystem::path &path);

}; // namespace utils

#endif
