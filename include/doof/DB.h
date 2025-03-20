#ifndef DB_H
#define DB_H

#include <iostream>
#include <vector>
#include "sqlite3/sqlite3.h"
#include "doof/Food.h"
#include "doof/Customer.h"

using namespace std;

class Restaurant;
class Customer;

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
  vector<Restaurant> getRestaurants() const;
  Restaurant* getRestaurantByEmail(const string& email) const;
  bool restaurantEmailExists(const string& email) const;

  bool insertCustomer(Customer& customer) const;
  bool customerEmailExists(const string& email) const;
  Customer* getCustomerByEmail(const string& email) const;

  void insertFood(Food& food) const;
  Food getFoodById(int foodId);
  vector<Food> getMenu(const int restaurantId) const;

  bool insertOrder(Order& order);
  vector<Order> getOrdersByCustomerId(int customerId);
  vector<Order> getOrdersByRestaurantId(int customerId);
  bool updateOrderStatus(int orderId, OrderStatus newStatus);
};
#endif
