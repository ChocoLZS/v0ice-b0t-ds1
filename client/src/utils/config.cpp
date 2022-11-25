#include <utils/logger.hpp>
#include <utils/util.hpp>

#include "DslConfig.h"

namespace util {
namespace config {
argparse::ArgumentParser helper(int argc, char *argv[]) {
  argparse::ArgumentParser program("dsl-client",
                                   std::to_string(CLIENT_VERSION_MAJOR) + "." +
                                       std::to_string(CLIENT_VERSION_MINOR));
  program.add_argument("-s", "--server")
      .help("server address")
      .nargs(1)
      .default_value(client::config::SERVER_ADDRESS)
      .metavar("ADDRESS");
  program.add_argument("-p", "--port")
      .help("port to server")
      .nargs(1)
      .default_value(client::config::PORT)
      .scan<'u', unsigned short>()
      .metavar("PORT");
  program.add_argument("-d", "--debug")
      .help("show log debug info,if log mode open")
      .nargs(0)
      .default_value(client::config::DEBUG)
      .implicit_value(true);
  program.add_argument("-l", "--log")
      .help("path to save log file, empty for no log")
      .nargs(1)
      .default_value(client::config::LOG_PATH)
      .metavar("PATH");
  program.add_argument("-u", "--uid")
      .help("user id")
      .nargs(1)
      .scan<'i', int>()
      .metavar("UID");
  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    throw std::runtime_error(program.help().str());
  }
  return program;
}
void serviceInit(argparse::ArgumentParser program) {
  std::string server = program.get<std::string>("-s");
  std::string log = program.get<std::string>("-l");
  int port = program.get<unsigned short>("-p");
  bool debug = program.get<bool>("-d");
  int uid = program.get<int>("-u");
  client::config::LOG_PATH = log;
  client::config::SERVER_ADDRESS = server;
  client::config::PORT = port;
  client::config::DEBUG = debug;
  client::config::USERID = uid;
  util::logger::initLogger();
}

void serviceClose() {}
}  // namespace config
}  // namespace util