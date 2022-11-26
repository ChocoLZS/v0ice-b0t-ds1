#pragma once

#include <argparse/argparse.hpp>
#include <map>
#include <string>
#include <typing/type.hpp>
#include <vector>

namespace util {
namespace str {
const std::string WHITESPACE = " \n\r\t\f\v";
/**
 * @brief Trim the string
 * @param s The string to be trimmed
 * @param drop The characters to be trimmed
 * @return std::string The trimmed string
 */
std::string &trim(std::string &s, const std::string &drop = WHITESPACE);

/**
 * @brief Erace the whitespace in the string
 * @param s The string to be processed
 * @return std::vector<std::string> The vector of the tokens
 */
std::vector<std::string> eraseWhitespace(std::string &s);

/**
 * @brief Split the string into tokens
 * @param s The string to be split
 * @param delimiter The delimiter
 * @return std::vector\\<std::string\> The vector of the tokens
 */
std::vector<std::string> split(std::string s, std::string delimiter);
}  // namespace str


extern std::map<std::string, ActionType> action_mapping;
namespace config {
/**
 * @brief The helper function to parse the command line arguments
 * @param argc The number of arguments
 * @param argv The arguments
 * @return argparse::ArgumentParser The argument parser
 */
argparse::ArgumentParser helper(int argc, char *argv[]);

/**
* @brief Initialize the basic service link setting variables ,initializing database ,logger and parse the script.
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


namespace server {
namespace config {
extern unsigned short PORT;
extern std::string FILE_PATH;
extern std::string LOG_PATH;
extern std::string DB_PATH;
extern bool DEBUG;
}  // namespace config
}  // namespace server