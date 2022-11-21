#include <pthread.h>

#include <db/sqlite.hpp>
#include <interpreter/interpreter.hpp>
#include <lib/argparse/argparse.hpp>
#include <parser/parser.hpp>
#include <string>

#include "DslConfig.h"

argparse::ArgumentParser helper(int argc, char *argv[]) {
  argparse::ArgumentParser program("dsl",
                                   std::to_string(dsl_VERSION_MAJOR) + "." +
                                       std::to_string(dsl_VERSION_MINOR));
  program.add_argument("-f", "--file").help("").nargs(1);
  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  return program;
}

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program;
  try {
    program = helper(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  auto file = program.get<std::string>("-f");
  parser::ParseFile("../test/script.vb");
  init_db();

  interpreter::executor::Execute(1);

  close_db();
  return 0;
}