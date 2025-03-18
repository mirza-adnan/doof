#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "doof/enums.h"
#include "doof/Food.h"
#include "doof/User.h"
#include "doof/DB.h"
#include <queue>
#include <iomanip>
#include "doof/Order.h"

using namespace std;

class Restaurant : public User {
private:
  RestaurantType type;
  vector<Food> menu;
  vector<Order> orders;

public:
  Restaurant();

  Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type);

  Restaurant(int _id, const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type);

  ~Restaurant();

  // getters
  RestaurantType getType() const;
  const vector<Food>& getMenu();

  // setters
  void setType(const RestaurantType& _type);
  void setMenu(vector<Food> _menu);
  void addToMenu(Food item);

  const vector<Order> getOrders();
  void addOrder(Order order);
  void displayOrders();

  void displayMenu();
};

#endif
