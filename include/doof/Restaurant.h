#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "doof/enums.h"
#include "doof/Food.h"

class Restaurant {
private:
  RestaurantType type;
  vector<Food*> menu;

public:
  Restaurant();

  Restaurant(RestaurantType _type);

  ~Restaurant();

  // getters
  RestaurantType getType() const;

  // setters
  void setType(const RestaurantType& _type);
};

#endif