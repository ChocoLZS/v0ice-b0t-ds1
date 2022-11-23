#pragma once
#include <rest_rpc/rest_rpc.hpp>

namespace service {
void clientStart();
std::string printBranches(std::map<std::string, std::string> branches);
}  // namespace service
