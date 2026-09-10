#include <CLI/CLI.hpp>
#include <print>

int main(int argc, char **argv) {
  CLI::App app{"lcj++"};

  std::string name;
  app.add_option("-n,--name", name, "Your name")->required();

  CLI11_PARSE(app, argc, argv);

  std::println("Hello,  {}", name);
}
