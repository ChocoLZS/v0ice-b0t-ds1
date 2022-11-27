#pragma once
#include <sqlite3.h>

#include <nlohmann/json.hpp>
#include <optional>
using json = nlohmann::json;

void init_db();
void close_db();

extern sqlite3 *db_fd;

namespace sqlgen {

/**
 * @brief Get the user's information from database
 * @param id The id of the user
 * @return std::optional<json> The user's information
 */
std::optional<json> getUser(int id);
}  // namespace sqlgen