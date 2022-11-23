#pragma once

#include <argparse/argparse.hpp>
#include <map>
#include <string>
#include <typing/type.hpp>
#include <vector>

namespace util {
namespace str {
const std::string WHITESPACE = " \n\r\t\f\v";
std::string &trim(std::string &s, const std::string &drop = WHITESPACE);
std::string getCommand(std::string &s);
std::vector<std::string> eraceWhitespace(std::string &s);
std::vector<std::string> split(std::string s, std::string delimiter);
}  // namespace str

extern std::map<std::string, ActionType> action_mapping;
namespace config {
argparse::ArgumentParser helper(int argc, char *argv[]);
void serviceInit(argparse::ArgumentParser program);
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