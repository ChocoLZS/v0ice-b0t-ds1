#include <stdio.h>

#include <db/sqlite.hpp>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace sqlgen {
std::optional<json> getUser(int id) {
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db_fd, "SELECT * FROM userinfo WHERE id = ?;", -1, &stmt,
                     NULL);
  sqlite3_bind_int(stmt, 1, id);
  int rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
    json user;
    user["$id"] = sqlite3_column_int(stmt, 0);
    user["$name"] = std::string(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    user["$amount"] = sqlite3_column_int(stmt, 2);
    user["$credit"] = sqlite3_column_int(stmt, 3);
    user["$data"] = sqlite3_column_int(stmt, 4);
    return user;
  }
  return std::nullopt;
}
}  // namespace sqlgen