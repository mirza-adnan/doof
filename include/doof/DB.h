#ifndef DB_H
#define DB_H

#include <iostream>
#include "sqlite3/sqlite3.h"
#include "doof/Restaurant.h"
#include "doof/Food.h"

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
  void insertFood(Food& food) const;
  bool restaurantEmailExists(const string& email) const;
};

#endif