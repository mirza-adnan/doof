#include "doof/Restaurant.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(RestaurantType _type) {
  type = _type;
}

Restaurant::~Restaurant() {
  for (int i = 0; i < menu.size(); i++) {
    delete menu[i];
  }
}

// getters
RestaurantType Restaurant::getType() const {
  return type;
}

// setters
void Restaurant::setType(const RestaurantType& _type) {
  type = _type;
}
