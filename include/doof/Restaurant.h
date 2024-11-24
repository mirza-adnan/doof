#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include "doof/enums.h"

class Restaurant {
private:
  RestaurantType type;

public:
  Restaurant();

  Restaurant(RestaurantType _type);

  // getters
  RestaurantType getType() const;

  // setters
  void setType(const RestaurantType& _type);
};

#endif