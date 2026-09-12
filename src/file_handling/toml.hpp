#ifndef TOML_H
#define TOML_H
#include <string_view>
#pragma once

#include "testcase.hpp"
#include <filesystem>
#include <toml++/toml.hpp>

struct TomlHandler {
  toml::table tbl;

  TomlHandler(const std::filesystem::path &path)
      : tbl(toml::parse_file(path.string())) {}

  toml::array *GetArray();

  void Add(const TestCase &ts);
  void Remove(std::string_view);
  void Reset();
  void Edit(const TestCase &ts);
  void Write();
};

#endif