#include <iostream>
#include <filesystem>
#include <parser/parser.hpp>
#include <string>
#include <set>
#include <algorithm>

int main() {
  std::string curPath = std::filesystem::current_path();
  int index = curPath.find("/bin/test");
  if (index == std::string::npos) {
    index = curPath.find("/build/test");
  }
  curPath = curPath.substr(0, index) + "/data/test-scripts";
  std::vector<std::string> files;
  for (const auto &entry : std::filesystem::directory_iterator(curPath)) {
    files.push_back(entry.path());
  }
  std::sort(files.begin(), files.end());
  for(auto file : files) {
      Script script;
    try {
      std::cout << file << std::endl;
      parser::ParseFile(file, script);
      std::cout << "ParseFile success" << std::endl;
    } catch (std::runtime_error &err) {
      std::cout << err.what() << std::endl;
    }
  }
}
