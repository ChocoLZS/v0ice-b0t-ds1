#pragma once

#include <argparse/argparse.hpp>
#include <string>

namespace util {
namespace config {
/**
 * @brief Parses the command line arguments
 * @param argc The number of arguments
 * @param argv The arguments
 * @return argparse::ArgumentParser The arg parser
 */
argparse::ArgumentParser helper(int argc, char *argv[]);

/**
 * @brief Initialize the basic service link setting variables ,logger and etc.
 * @param program The arg parser
 * @return void
 */
void serviceInit(argparse::ArgumentParser program);

/**
 * @brief Close the some service.
 */
void serviceClose();
}  // namespace config
}  // namespace util
namespace client {
namespace config {
extern unsigned short PORT;
extern std::string SERVER_ADDRESS;
extern std::string LOG_PATH;
extern bool DEBUG;
extern int USER_ID;
}  // namespace config
}  // namespace client
