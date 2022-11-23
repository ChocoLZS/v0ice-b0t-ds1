#pragma once
#include <sqlite3.h>

#include <nlohmann/json.hpp>
#include <optional>
using json = nlohmann::json;

void init_db();
void close_db();

extern sqlite3 *db_fd;

namespace sqlgen {
std::optional<json> getUser(int id);
}  // namespace sqlgen