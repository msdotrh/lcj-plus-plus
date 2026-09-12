#ifndef UTILS_H
#define UTILS_H
#include <memory>
#pragma once

#include "file_handling/testcase.hpp"
#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>
#include <toml++/toml.hpp>

namespace utils {

inline bool is_ascii(const std::string &s) {
  return std::ranges::all_of(s, [](unsigned char c) { return c < 128; });
}

void create_file(const std::filesystem::path &path);

toml::const_array_iterator find(std::string_view name,
                                const toml::array &array);

}; // namespace utils

#endif