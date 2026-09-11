#ifndef ULTIS_H
#define ULTIS_H
#pragma once

#include <algorithm>
#include <string>
#include <filesystem>

namespace utils {
inline bool is_ascii(const std::string& s) {
  return std::ranges::all_of(s, [](unsigned char c) { return c < 128; });
}

void create_file(const std::filesystem::path &path);
};

#endif