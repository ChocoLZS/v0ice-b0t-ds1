#pragma once
#include <map>
#include <string>
#include <typing/type.hpp>

namespace interpreter {
void initInterpreter();
namespace executor {
void Execute(int id);
std::string generateSpeak(Step step, std::optional<json> userInfo);
} // namespace executor
}  // namespace interpreter
