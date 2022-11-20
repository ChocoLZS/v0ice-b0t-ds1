#include "DslConfig.h"
#include <argparse/argparse.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << dsl_VERSION_MAJOR << "." << dsl_VERSION_MINOR << std::endl;
  argparse::ArgumentParser program("program_name");

  program.add_argument("square")
    .help("display the square of a given integer")
    .scan<'i', int>();

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  auto input = program.get<int>("square");
  std::cout << (input * input) << std::endl;

  return 0;
  return 0;
}