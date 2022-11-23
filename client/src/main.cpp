#include <exception>
#include <service/client.hpp>
#include <utils/util.hpp>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program;
  try {
    program = util::config::helper(argc, argv);
    util::config::serviceInit(program);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::exit(1);
  }
  service::clientStart();
  util::config::serviceClose();
  return 0;
}