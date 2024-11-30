#ifndef DB_H
#define DB_H

#include <iostream>
#include "sqlite3/sqlite3.h"
#include "doof/Restaurant.h"

using namespace std;

class DB {
private:
  sqlite3* db;

public:
  DB();
  ~DB();

  sqlite3*& getDb();
  bool execute(const string& sql) const;
  void createTables();
  bool insertRestaurant(Restaurant& restaurant) const;
  void getRestaurants() const;
};

#endif