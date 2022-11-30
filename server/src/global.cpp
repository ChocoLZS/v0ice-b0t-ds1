#include <typing/type.hpp>
#include <utils/util.hpp>

/**
 * @brief The mapping of the action to the action type
 */
std::map<std::string, int> util::action_mapping = {
    {"Step", (int)ActionType::Step},      {"Listen", (int)ActionType::Listen},
    {"Branch", (int)ActionType::Branch},  {"Silence", (int)ActionType::Silence},
    {"Speak", (int)ActionType::Speak},    {"Exit", (int)ActionType::Exit},
    {"Default", (int)ActionType::Default}};

/**
 * @brief The global script AST
 */
Script script;

namespace server {
namespace config {

unsigned short PORT = 9000;
std::string FILE_PATH = "./script";
std::string LOG_PATH = "";
std::string DB_PATH = "./db/dsl.db";
bool DEBUG = false;

}  // namespace config
}  // namespace server