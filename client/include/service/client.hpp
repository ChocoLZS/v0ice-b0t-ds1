#pragma once
#include <rest_rpc/rest_rpc.hpp>

namespace service {
void clientStart();

/**
* @brief Print next optional steps
* @param branches The branches of the next optional steps
*/
std::string printBranches(std::map<std::string, std::string> branches);
}  // namespace service
