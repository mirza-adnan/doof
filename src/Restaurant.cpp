#include "doof/Restaurant.h"

extern DB db;

Restaurant::Restaurant() {}

Restaurant::Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_name, _email, _pass, _contact, _addr) {
  type = _type;
}

Restaurant::Restaurant(int _id, const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_id, _name, _email, _pass, _contact, _addr) {
  type = _type;
}

// getters
RestaurantType Restaurant::getType() const {
  return type;
}

const vector<Food>& Restaurant::getMenu() const {
  return menu;
}

// setters
void Restaurant::setType(const RestaurantType& _type) {
  type = _type;
}

void Restaurant::setMenu(vector<Food> _menu) {
  menu = _menu;
}

void Restaurant::addToMenu(Food item) {
  db.insertFood(item);
  menu.push_back(item);
  cout << item.getName() << "\n";
}

void Restaurant::displayMenu() {
  for (int i = 0; i < menu.size(); i++) {
    printf("%d. \t %s \t %f\n", i + 1, menu[i].getName().c_str(), menu[i].getPrice());
  }
}

