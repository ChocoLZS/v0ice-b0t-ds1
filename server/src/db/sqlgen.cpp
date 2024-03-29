/**
 * @details This function returns value by accessing the database.
 */
#include <stdio.h>

#include <db/sqlite.hpp>
#include <optional>
#include <string>
#include <utils/logger.hpp>

namespace sqlgen {

std::optional<json> getUser(int id) {
  PLOG_DEBUG << "Getting id : " << std::to_string(id)
             << " , user info from database...";
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
    user["$data"] = std::string(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
    return user;
  }
  return std::nullopt;
}
}  // namespace sqlgen