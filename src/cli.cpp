#include "cli.hpp"
#include "CLI/CLI.hpp"
#include "globals.hpp"
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <optional>
#include <print>
#include <variant>

using Commands = std::variant<Command::Add, Command::Remove, Command::Reset,
                              Command::Run, Command::Edit, Command::List>;

void Command::Add::execute() {}

void Command::Remove::execute() {}

void Command::Reset::execute() {}

void Command::Run::execute() {}

void Command::Edit::execute() {}

void Command::List::execute() {}

void CLI_init() {
  std::string name;
  std::filesystem::path file, dir;
  std::optional<std::filesystem::path> _input_file, _output_file;
  std::optional<std::size_t> _memory_limit;
  std::optional<std::chrono::milliseconds> _time_limit_in_milliseconds;

  CLI::App app("simple local judges", "lcj++");

  CLI::App *add = app.add_subcommand("add", "Add new testcase");
  add->alias("init");
  // add name file dir
  // optional: --output, --input, --time, --memory
  add->add_option("name", name, "The new testcase's name")->required();
  add->add_option("file", file, "The testcase's execution file")->required();
  add->add_option(
         "io_directory", dir,
         "The program will use this directory to compare tokens / get input")
      ->required();

  add->add_option("--input", _input_file,
                  "Input streams to read (default: stdin)");
  add->add_option("--output", _output_file,
                  "Output streams to read (default: stdout)");
  add->add_option("--time_limit", _time_limit_in_milliseconds,
                  "Set time limit for each case to process");
  add->add_option("--memory-limit", _memory_limit,
                  "Set memory limit for each case to process");

  CLI::App *remove = app.add_subcommand("remove", "Remove a testcase");
  remove->alias("rm");
  remove->alias("delete");
  remove->alias("de");
  // remove name
  remove->add_option("name", name, "The testcase's name you want to delete")
      ->required();

  CLI::App *reset =
      app.add_subcommand("reset", "Reset / Remove every testcase");
  // reset

  CLI::App *run = app.add_subcommand("run", "Run a testcase");
  run->alias("r");
  // run testcase
  // optional: --output, --input, --time, --memory
  run->add_option("testcase", name,
                  "The name of the testcase you want to execute")
      ->required();
  run->add_option("--input", _input_file, "Overrides the input streams");
  run->add_option("--output", _output_file, "Overrides the output streams");
  run->add_option("--time", _time_limit_in_milliseconds,
                  "Overrides time limit");
  run->add_option("--memory", _memory_limit, "Overrides memory limit");

  CLI::App *edit = app.add_subcommand("edit", "Edit a testcase");

  CLI::App *list =
      app.add_subcommand("list", "List current testcase inside testcases.toml");

  try {
    app.parse(argc_g, argv_g);
  } catch (const CLI::ParseError &e) {
    app.exit(e);
    return;
  }

  Commands cmd;

  if (add->parsed()) {
    cmd = Command::Add{name,
                       file,
                       dir,
                       _input_file,
                       _output_file,
                       _memory_limit,
                       _time_limit_in_milliseconds};
  } else if (remove->parsed()) {
    cmd = Command::Remove{name};

  } else if (reset->parsed()) {
    cmd = Command::Reset{};
  } else if (run->parsed()) {
    cmd = Command::Run{name, _input_file, _output_file, _memory_limit,
                       _time_limit_in_milliseconds};
  } else if (list->parsed()) {
    cmd = Command::List{};
  } else {
    std::println("Nothing matched!");
    return;
  }

  std::visit([](auto &cmd_p) { cmd_p.execute(); }, cmd);
}