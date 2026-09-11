#include "globals.hpp"
#include <filesystem>
#include <optional>

int g_argc = 0;
char **g_argv = nullptr;

std::filesystem::path g_current_path = std::filesystem::current_path();

std::filesystem::path g_toml_path = g_current_path / "config/testcase.toml";