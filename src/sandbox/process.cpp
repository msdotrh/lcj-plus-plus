#include "process.hpp"
#include <iostream>
#include <reproc++/drain.hpp>
#include <reproc++/reproc.hpp>
#include <system_error>

int Process::Run() {
  reproc::process process;
  std::vector<std::string> cmd = {"g++"};
  auto ec = process.start(cmd);

  reproc::sink::string sinkout{output.standard_out};
  reproc::sink::string sinkerr{output.standard_err};
  ec = reproc::drain(process, sinkout, sinkerr);

  int status = 0;
  std::tie(status, ec) = process.stop(reproc::options().stop);

  std::cout << output.standard_err << " " << output.standard_out << std::flush;

  return status;
}
