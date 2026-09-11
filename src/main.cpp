#include "cli.hpp"
#include "file_handling/testcase.hpp"
#include "file_handling/toml.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include <CLI/CLI.hpp>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <print>

int main(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;

  if (!std::filesystem::exists(g_toml_path)) {
    std::println("Can not find {}! Creating file...", g_toml_path.string());
    utils::create_file(g_toml_path);
  }

  // parse toml
  auto toml_ptr = std::make_unique<TomlHandler>(g_toml_path);

  toml_ptr->Add(TestCase{"name", "file", "path", std::nullopt, std::nullopt,
                         std::nullopt, std::nullopt});

  // end of program, write to toml.
  toml_ptr->Write();
}
