#pragma once

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
}  // namespace util
