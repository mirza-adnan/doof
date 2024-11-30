#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "doof/enums.h"
#include "doof/Food.h"
#include "doof/User.h"

class Restaurant : public User {
private:
  RestaurantType type;
  vector<Food*> menu;

public:
  Restaurant();

  Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type);

  ~Restaurant();

  // getters
  RestaurantType getType() const;

  // setters
  void setType(const RestaurantType& _type);
};

#endif