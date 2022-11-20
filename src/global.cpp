#include <typing/type.hpp>
#include <utils/util.hpp>

std::map<std::string, util::ActionType> util::action_mapping = {
    {"Step", util::ActionType::Step},
    {"Listen", util::ActionType::Listen},
    {"Branch", util::ActionType::Branch},
    {"Silence", util::ActionType::Silence},
    {"Speak", util::ActionType::Speak},
    {"Exit", util::ActionType::Exit},
    {"Default", util::ActionType::Default}};

Script script = Script();
