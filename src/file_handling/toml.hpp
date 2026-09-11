#ifndef TOML_H
#define TOML_H
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
  void Remove(const TestCase &ts);
  void Reset();
  void Edit(const TestCase &ts);
  void Write();
};

#endif