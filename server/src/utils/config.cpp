#include <db/sqlite.hpp>
#include <parser/parser.hpp>
#include <utils/logger.hpp>
#include <utils/util.hpp>

#include "DslConfig.h"
extern Script script;

namespace util {
namespace config {
argparse::ArgumentParser helper(int argc, char *argv[]) {
  argparse::ArgumentParser program("dsl",
                                   std::to_string(SERVER_VERSION_MAJOR) + "." +
                                       std::to_string(SERVER_VERSION_MINOR));
  program.add_argument("-f", "--file")
      .help("path to script file")
      .nargs(1)
      .default_value(server::config::FILE_PATH)
      .metavar("PATH");
  program.add_argument("-p", "--port")
      .help("port to listen")
      .nargs(1)
      .default_value(server::config::PORT)
      .scan<'u', unsigned short>()
      .metavar("PORT");
  program.add_argument("-l", "--log")
      .help("path to save log file")
      .nargs(1)
      .default_value(server::config::LOG_PATH)
      .metavar("PATH");
  program.add_argument("-d", "--debug")
      .help("debug mode")
      .nargs(0)
      .default_value(server::config::DEBUG)
      .implicit_value(true);
  program.add_argument("--database")
      .help("path to database file")
      .nargs(1)
      .default_value(server::config::DB_PATH)
      .metavar("PATH");
  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    throw std::runtime_error(program.help().str());
  }
  return program;
}

void serviceInit(argparse::ArgumentParser program) {
  // getting the configurations
  std::string file = program.get<std::string>("-f");
  int port = program.get<unsigned short>("-p");
  std::string log = program.get<std::string>("-l");
  bool debug = program.get<bool>("-d");
  std::string database = program.get<std::string>("--database");

  server::config::FILE_PATH = file;
  server::config::PORT = port;
  server::config::LOG_PATH = log;
  server::config::DEBUG = debug;
  server::config::DB_PATH = database;
  // initializing
  util::logger::initLogger();
  try {
    init_db();
    Script new_script;
    parser::ParseFile(server::config::FILE_PATH, new_script);

    // global variable
    script = new_script;
  } catch (std::runtime_error &err) {
    throw err;
  }
}

void serviceClose() { close_db(); }
}  // namespace config
}  // namespace util
