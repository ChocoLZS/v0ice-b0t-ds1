#include <iostream>
#include <utils/util.hpp>

namespace util {
namespace str {

std::string &trim(std::string &s, const std::string &drop) {
  if (s.empty()) {
    return s;
  }
  s.erase(0, s.find_first_not_of(drop));
  s.erase(s.find_last_not_of(drop) + 1);
  return s;
}

std::vector<std::string> eraseWhitespace(std::string &s) {
  //  双指针写法
  std::vector<std::string> tokens;
  size_t pos = 0;
  for (size_t i = 0; i < s.size(); i++) {
    // skip comments
    if (s[i] == '#') {
      if (!std::isspace(s[i - 1])) {
        tokens.push_back(s.substr(pos, i - pos));
      }
      break;
    }
    if (std::isspace(s[pos])) {
      pos++;
      continue;
    }
    if (std::isspace(s[i])) {
      tokens.push_back(s.substr(pos, i - pos));
      pos = i + 1;
    } else if (i == s.size() - 1) {
      tokens.push_back(s.substr(pos, i - pos + 1));
    }
  }
  return tokens;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
  std::vector<std::string> strs;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std ::string::npos) {
    token = s.substr(0, pos);
    strs.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  token = s.substr(0, pos);
  strs.push_back(token);
  return strs;
}
}  // namespace str

}  // namespace util