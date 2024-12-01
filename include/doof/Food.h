#ifndef FOOD_H
#define FOOD_H

#include <string>
using namespace std;

class Food {
private:
  string name;
  float price;
  bool available;
  int id;
  int restaurantId;

public:
  Food();

  Food(const string& _name, float _price, bool _available, int _restaurantId);

  // getters
  string getName() const;
  float getPrice() const;
  bool isAvailable() const;
  int getId() const;
  int getRestaurantId() const;

  // setters
  void setName(const string& _name);
  void setPrice(const float _price);
  void setAvailable(const bool _available);
  void setId(const int _id);
  void setRestaurantId(const int _restaurantId);
};

#endif
