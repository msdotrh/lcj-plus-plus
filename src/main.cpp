#include "cli.hpp"
#include "file_handling/toml.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include <CLI/CLI.hpp>
#include <filesystem>
#include <memory>
#include <print>

int main(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;

  if (!std::filesystem::exists(g_toml_path)) {
    std::println("Can not find {}! Creating file...", g_toml_path.string());
    utils::create_file(g_toml_path);
  }

  auto toml = std::make_unique<TomlHandler>(g_toml_path);

  CLI_init();
}
