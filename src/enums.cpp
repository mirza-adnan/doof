#include "doof/enums.h"

istream& operator>>(istream& is, RestaurantType& type) {
  int a;
  is >> a;
  type = static_cast<RestaurantType>(a);
  return is;
}

ostream& operator<<(ostream& os, const RestaurantType& type) {
  if (type == RESTAURANT_TYPE_FAST_FOOD) {
    os << "Fast Food";
  }
  else if (type == RESTAURANT_TYPE_CAFE) {
    os << "Cafe";
  }
  else if (type == RESTAURANT_TYPE_FINE_DINING) {
    os << "Fine Dining";
  }
  return os;
}
