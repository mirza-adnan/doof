#include "doof/Restaurant.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_name, _email, _pass) {
  address = _addr;
  contact = _contact;
  type = _type;
}

Restaurant::~Restaurant() {
  for (int i = 0; i < menu.size(); i++) {
    delete menu[i];
  }
}

// getters
string Restaurant::getAddress() const {
  return address;
}

string Restaurant::getContact() const {
  return contact;
}

RestaurantType Restaurant::getType() const {
  return type;
}

// setters
void Restaurant::setAddress(const string& _addr) {
  address = _addr;
}

void Restaurant::setContact(const string& _contact) {
  contact = _contact;
}

void Restaurant::setType(const RestaurantType& _type) {
  type = _type;
}
