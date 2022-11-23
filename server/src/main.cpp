#include <service/server.hpp>
#include <utils/logger.hpp>
#include <utils/util.hpp>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program;
  // Initialize the parameters.
  try {
    program = util::config::helper(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what();
    std::exit(1);
  }
  // Logger enabled.
  try {
    util::config::serviceInit(program);
  } catch (const std::runtime_error &err) {
    PLOG_ERROR << err.what();
    std::exit(1);
  }
  service::serverStart();
  util::config::serviceClose();
  return 0;
}
