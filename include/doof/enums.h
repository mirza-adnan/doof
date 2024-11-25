#ifndef ENUMS_H
#define ENUMS_H

#include <iostream>
using namespace std;

enum RestaurantType {
  RESTAURANT_TYPE_FAST_FOOD,
  RESTAURANT_TYPE_CAFE,
  RESTAURANT_TYPE_FINE_DINING,
  RESTAURANT_TYPE_TOTAL
};

istream& operator >> (istream& is, RestaurantType& type) {
  int a;
  is >> a;
  type = static_cast<RestaurantType>(a);

  return is;
}

ostream& operator << (ostream& os, RestaurantType& type) {
  if (type == RESTAURANT_TYPE_FAST_FOOD) {
    os << "Fast Food";
  }
  else if (type == RESTAURANT_TYPE_CAFE) {
    os << "Cafe";
  }
  else if (type == RESTAURANT_TYPE_FINE_DINING) {
    os << "Fine Dining";
  }
}

enum AuthType {
  AUTH_TYPE_RESTAURANT,
  AUTH_TYPE_CUSTOMER
};

#endif