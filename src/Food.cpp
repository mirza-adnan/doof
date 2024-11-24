#include "doof/Food.h"

// Default constructor
Food::Food() {}

Food::Food(const string& _name, float _price, bool _available, int _restaurantId) {
  name = _name;
  price = _price;
  available = _available;
  restaurantId = _restaurantId;
}

// getters
string Food::getName() const {
  return name;
}

float Food::getPrice() const {
  return price;
}

bool Food::isAvailable() const {
  return available;
}

int Food::getId() const {
  return id;
}

int Food::getRestaurantId() const {
  return restaurantId;
}

// setters
void Food::setName(const string& _name) {
  name = _name;
}

void Food::setPrice(float _price) {
  price = _price;
}

void Food::setAvailable(bool _available) {
  available = _available;
}

void Food::setId(int _id) {
  id = _id;
}

void Food::setRestaurantId(int _restaurantId) {
  restaurantId = _restaurantId;
}
