#include "toml.hpp"
#include "../globals.hpp"
#include "testcase.hpp"
#include <cstdint>
#include <exception>
#include <fstream>
#include <print>
#include <toml++/impl/table.hpp>

toml::array *TomlHandler::GetArray() {
  auto *array = tbl["testcases"].as_array();

  if (!array) {
    tbl.insert("testcases", toml::array{});
    array = tbl["testcases"].as_array();
  }

  return array;
}

void TomlHandler::Add(const TestCase &ts) {
  auto array = GetArray();

  toml::table table{
      {"name", ts.name},
      {"file", ts.file.string()},
      {"io-dir", ts.dir.string()},
  };

  if (ts.input_file)
    table.insert("input-file", ts.input_file->string());

  if (ts.output_file)
    table.insert("output-file", ts.output_file->string());

  if (ts.time_limit)
    table.insert("time-limit", ts.time_limit->count());

  if (ts.memory)
    table.insert("memory", static_cast<int64_t>(*ts.memory));

  array->push_back(std::move(table));
}

void TomlHandler::Edit(const TestCase &ts) {}

void TomlHandler::Remove(const TestCase &ts) {}

void TomlHandler::Reset() {}

void TomlHandler::Write() {
  std::ofstream file(g_toml_path);
  if (!file) {
    std::println(stderr, "Can not open file {}! Terminate program",
                 g_toml_path.string());
    std::terminate();
  }
  std::println("Writing the toml table to {}", g_toml_path.string());
  file << tbl << '\n';
}
