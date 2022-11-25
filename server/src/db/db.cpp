#include <db/sqlite.hpp>
#include <utils/logger.hpp>
#include <utils/util.hpp>

sqlite3 *db_fd;

void init_db() {
  PLOG_INFO << "Initializing database...";
  int rc;
  // change by command or default
  rc = sqlite3_open_v2(server::config::DB_PATH.c_str(), &db_fd,SQLITE_OPEN_READONLY, NULL);
  if (rc) {
    throw std::runtime_error(
        "Can't open database: " + std::string(sqlite3_errmsg(db_fd)) +
        " ,maybe you can check your database path {"
        + server::config::DB_PATH + "}");
  } else {
    PLOG_INFO << "Opened database successfully!";
  }
}

void close_db() { sqlite3_close(db_fd); }