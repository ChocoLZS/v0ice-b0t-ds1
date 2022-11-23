#pragma once

#include <argparse/argparse.hpp>
#include <string>

namespace util {
namespace config {
argparse::ArgumentParser helper(int argc, char *argv[]);
void serviceInit(argparse::ArgumentParser program);
void serviceClose();
}  // namespace config
}  // namespace util
namespace client {
namespace config {
extern unsigned short PORT;
extern std::string SERVER_ADDRESS;
extern std::string LOG_PATH;
extern bool DEBUG;
extern int USERID;
}  // namespace config
}  // namespace client
