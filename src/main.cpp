#include "sqlite3/sqlite3.h"
#include <iostream>
using namespace std;

int main() {
  sqlite3* db;
  int exit = sqlite3_open("./db/doof.dev.db", &db);

  sqlite3_close(db);
  return 0;
}