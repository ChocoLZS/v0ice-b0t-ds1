#include <pthread.h>

#include <argparse/argparse.hpp>
#include <db/sqlite.hpp>
#include <interpreter/interpreter.hpp>
#include <parser/parser.hpp>

int main() {

  parser::ParseFile("../test/script.vb");
  init_db();

  interpreter::executor::Execute(1);

  close_db();
  return 0;
}