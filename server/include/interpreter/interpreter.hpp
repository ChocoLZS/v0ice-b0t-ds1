#pragma once
#include <map>
#include <string>
#include <typing/type.hpp>

namespace interpreter {
namespace executor {
/**
 * @deprecated
 * @brief Execute the script by every user
 * @param id The id of the user
 */
void Execute(int id);

/**
 * @brief Generate the speak string
 * @param step The step to be spoken with its speak member
 * @param userInfo The user info, access by the variable name
 * @return The speak string
 */
std::string generateSpeak(Step step, std::optional<json> userInfo);
}  // namespace executor
}  // namespace interpreter
