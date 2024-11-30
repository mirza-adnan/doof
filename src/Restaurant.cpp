#include "doof/Restaurant.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_name, _email, _pass, _contact, _addr) {
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
