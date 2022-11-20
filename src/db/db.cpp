#include <stdio.h>

#include <cstdlib>
#include <db/sqlite.hpp>

sqlite3 *db_fd;

void init_db() {
  int rc;
  // change by command or default
  rc = sqlite3_open("../db/dsl.db", &db_fd);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_fd));
    exit(0);
  } else {
    fprintf(stderr, "Opened database successfully\n");
  }
}

void close_db() { sqlite3_close(db_fd); }