#include "doof/Food.h"

// Default constructor
Food::Food() {}

Food::Food(const string& _name, float _price, int _restaurantId) {
  name = _name;
  price = _price;
  restaurantId = _restaurantId;
}

Food::Food(int _id, const string& _name, float _price, int _restaurantId) {
  id = _id;
  name = _name;
  price = _price;
  restaurantId = _restaurantId;
}

// getters
const string& Food::getName() const {
  return name;
}

float Food::getPrice() const {
  return price;
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

void Food::setPrice(const float _price) {
  price = _price;
}

void Food::setId(int _id) {
  id = _id;
}

void Food::setRestaurantId(const int _restaurantId) {
  restaurantId = _restaurantId;
}
