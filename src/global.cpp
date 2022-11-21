#include <typing/type.hpp>
#include <utils/util.hpp>

/**
 * @brief The mapping of the action to the action type
 */
std::map<std::string, ActionType> util::action_mapping = {
    {"Step", ActionType::Step},      {"Listen", ActionType::Listen},
    {"Branch", ActionType::Branch},  {"Silence", ActionType::Silence},
    {"Speak", ActionType::Speak},    {"Exit", ActionType::Exit},
    {"Default", ActionType::Default}};

/**
 * @brief The global script AST
 */
Script script;
