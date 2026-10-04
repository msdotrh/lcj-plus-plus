#ifndef TOML_H
#define TOML_H
#pragma once

#include "testcase.hpp"
#include <filesystem>
#include <memory>
#include <toml++/toml.hpp>

struct TomlHandler {
  toml::table tbl;

  TomlHandler(const std::filesystem::path &path)
      : tbl(toml::parse_file(path.string())) {}

  toml::array *GetArray();

  void Add(const TestCase &ts);
  void Remove(std::string_view);
  void Reset();
  void Edit(TestCaseOptional &tso);
  void Write();
  toml::array_iterator Find(std::string_view name, toml::array &array);
  std::unique_ptr<TestCase> get(toml::array_iterator it);
};

#endif
