#ifndef DB_H
#define DB_H

#include <iostream>
#include <vector>
#include "sqlite3/sqlite3.h"
#include "doof/Food.h"

using namespace std;

class Restaurant;

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
  Restaurant* getRestaurantByEmail(const string& email) const;
  bool restaurantEmailExists(const string& email) const;

  void insertFood(Food& food) const;
  vector<Food> getMenu(const int restaurantId) const;
};

#endif
