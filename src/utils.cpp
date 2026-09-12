#include "utils.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <print>
#include <string>
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

toml::const_array_iterator utils::find(std::string_view name,
                                       const toml::array &array) {
  // Try to find a testcase named {name}, return a iterator to that TestCase in
  // the arrray
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
