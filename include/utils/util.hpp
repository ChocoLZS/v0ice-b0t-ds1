#pragma once

#include <map>
#include <string>
#include <vector>

namespace util {
namespace str {
const std::string WHITESPACE = " \n\r\t\f\v";
std::string &trim(std::string &s, const std::string &drop = WHITESPACE);
std::string getCommand(std::string &s);
std::vector<std::string> eraceWhitespace(std::string &s);
std::vector<std::string> split(std::string s, std::string delimiter);
}  // namespace str
enum class ActionType { Step, Listen, Branch, Silence, Speak, Exit, Default };
extern std::map<std::string, util::ActionType> action_mapping;
}  // namespace util
