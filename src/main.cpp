#include "sqlite3/sqlite3.h"
#include <iostream>
#include "doof/User.h"
#include "doof/Restaurant.h"
#include "doof/DB.h"
using namespace std;

int main() {
  DB db;
  // db.execute("DROP TABLE IF EXISTS User;");
  // db.execute("DROP TABLE IF EXISTS Restaurant;");
  db.createTables();

  Restaurant res("bfc", "bfc@email.com", "password", "01610210210", "uttara, dhaka", RESTAURANT_TYPE_FAST_FOOD);

  db.insertRestaurant(res);
  db.getRestaurants();
}