#ifndef FOOD_H
#define FOOD_H

#include <string>
using namespace std;

class Food {
private:
  string name;
  float price;
  int id;
  int restaurantId;

public:
  Food();

  Food(const string& _name, float _price, int _restaurantId);

  // getters
  const string& getName() const;
  float getPrice() const;
  int getId() const;
  int getRestaurantId() const;

  // setters
  void setName(const string& _name);
  void setPrice(const float _price);
  void setId(const int _id);
  void setRestaurantId(const int _restaurantId);
};

#endif
