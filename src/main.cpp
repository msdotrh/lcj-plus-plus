#include "cli.hpp"
#include "globals.hpp"
#include <CLI/CLI.hpp>

int main(int argc, char **argv) {
  argc_g = argc;
  argv_g = argv;
  CLI_init();
}
