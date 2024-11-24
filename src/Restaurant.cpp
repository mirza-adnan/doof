#include "Restaurant.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(RestaurantType _type) {
  type = _type;
}

// getters
RestaurantType Restaurant::getType() const {
  return type;
}

// setters
void Restaurant::setType(const RestaurantType& _type) {
  type = _type;
}
