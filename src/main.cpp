#include "sqlite3/sqlite3.h"
#include <iostream>
#include "doof/User.h"
#include "doof/Restaurant.h"
#include "doof/DB.h"
#include "doof/Food.h"
using namespace std;

int main() {
  DB db;
  db.execute("DROP TABLE IF EXISTS Restaurant;");
  db.execute("DROP TABLE IF EXISTS Food;");
  db.createTables();

  Restaurant res("American Burger", "am@email.com", "pass", "123456789", "Uttara", RESTAURANT_TYPE_FAST_FOOD);
  db.insertRestaurant(res);

  Food food("Cheese Burger", 280, true, res.getId());
  db.insertFood(food);

  cout << "Food id: " << food.getId() << "\n";
  cout << "Restaurant id: " << food.getRestaurantId() << "\n";

  db.getRestaurants();
}