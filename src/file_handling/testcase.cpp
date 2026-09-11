#include "testcase.hpp"
#include "../utils.hpp"
#include <exception>
#include <print>
#include <toml++/toml.hpp>

void TestCase::check_name() {
  if (!utils::is_ascii(this->name)) {
      std::println(stderr, "Name should only have ASCII characters! Terminating...");
      std::terminate();
  }
}