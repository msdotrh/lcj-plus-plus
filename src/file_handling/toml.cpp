#include "toml.hpp"
#include "../globals.hpp"
#include "../utils.hpp"
#include "testcase.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>
#include <print>
#include <string>
#include <string_view>
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

  if (TomlHandler::Find(ts.name, *array) != array->end()) {
    std::println(stderr, "{} already exists! Consider using edit, or remove.",
                 ts.name);
    std::terminate();
  }

  toml::table table{
      {"name", ts.name},
      {"file", std::filesystem::absolute(ts.file).string()},
      {"io-dir", std::filesystem::absolute(ts.dir).string()},
  };

  if (ts.input_file)
    table.insert("input-file", ts.input_file->string());

  if (ts.output_file)
    table.insert("output-file", ts.output_file->string());

  if (ts.time_limit)
    table.insert("time-limit", ts.time_limit->count());

  if (ts.memory)
    table.insert("memory-limit", static_cast<int64_t>(*ts.memory));

  array->push_back(std::move(table));
}

void TomlHandler::Edit(TestCaseOptional &tso) {
  auto array = GetArray();
  auto it = TomlHandler::Find(tso.name, *array);

  if (it == array->end()) {
    std::println(stderr,
                 "Testcase with the name {} do not exist!, consider using add",
                 tso.name);
    std::terminate();
  }

  auto tbl = it->as_table();
  if (tso.file) {
    tbl->insert_or_assign("file",
                          std::filesystem::absolute(*tso.file).string());
  }
  if (tso.dir) {
    tbl->insert_or_assign("io-dir",
                          std::filesystem::absolute(*tso.dir).string());
  }
  if (tso.input_file) {
    tbl->insert_or_assign("input-file",
                          std::filesystem::absolute(*tso.input_file).string());
  }
  if (tso.output_file) {
    tbl->insert_or_assign("output-file",
                          std::filesystem::absolute(*tso.output_file).string());
  }
  if (tso.time_limit) {
    tbl->insert_or_assign("time-limit", (*tso.time_limit).count());
  }
  if (tso.memory) {
    tbl->insert_or_assign("memory-limit", static_cast<int64_t>(*tso.memory));
  }
}

void TomlHandler::Remove(std::string_view name) {
  auto array = GetArray();
  auto it = TomlHandler::Find(name, *array);

  if (it == array->end()) {
    std::println(stderr, "Can not find testcase with the name: {}", name);
    std::terminate();
  }

  array->erase(it);
}

void TomlHandler::Reset() {
  utils::create_file(g_toml_path);
  tbl.clear();
}

void TomlHandler::Write() {
  std::ofstream file(g_toml_path);
  if (!file) {
    std::println(stderr, "Can not open file {}! Terminate program",
                 g_toml_path.string());
    std::terminate();
  }
  file << tbl << '\n';
}

toml::array_iterator TomlHandler::Find(std::string_view name,
                                       toml::array &array) {
  // Try to find a testcase named {name}, return a iterator to that TestCase in
  // the array
  for (auto it = array.begin(); it != array.end(); it++) {
    const auto &node = *it;

    const auto &tbl = node.as_table();

    if (!tbl)
      continue;

    auto name_node = tbl->get("name");
    if (!name_node)
      continue;

    auto testcase_name = name_node->value<std::string>();

    if (!testcase_name || *testcase_name != name)
      continue;

    // Found
    return it;
  }

  return array.end();
}

std::unique_ptr<TestCase> TomlHandler::get(toml::array_iterator &it) {
  auto tbl = *it->as_table();
  std::string name{tbl["name"].as_string()->value_or("0")};
  std::filesystem::path io_dir{tbl["io-dir"].as_string()->value_or("0")};
  std::filesystem::path file{tbl["file"].as_string()->value_or("0")};
  std::filesystem::path input_file{
      tbl["input-file"].as_string()->value_or("0")};
  std::filesystem::path output_file{
      tbl["output-file"].as_string()->value_or("0")};
  std::chrono::milliseconds time_limit{
      tbl["time-limit"].as_integer()->value_or(0)};
  std::size_t memory_limit{
      (size_t)tbl["memory-limit"].as_integer()->value_or(0)};

  std::unique_ptr<TestCase> TestCasePointer =
      std::make_unique<TestCase>(TestCase{name, file, io_dir});
  return TestCasePointer;
}
