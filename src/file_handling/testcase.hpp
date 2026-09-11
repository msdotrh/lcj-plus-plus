#ifndef TESTCASE_H
#define TESTCASE_H
#pragma once
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>

struct TestCase {
  std::string name;
  std::filesystem::path file, dir;
  std::optional<std::filesystem::path> input_file, output_file;
  std::optional<std::chrono::milliseconds> time_limit;
  std::optional<std::size_t> memory;

  void check_name();
};

#endif