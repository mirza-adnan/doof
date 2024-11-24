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

public:
  Food();

  Food(const string& _name, float _price, bool _available);

  // getters
  string getName() const;
  float getPrice() const;
  bool isAvailable() const;
  int getId() const;

  // setters
  void setName(const string& _name);
  void setPrice(float _price);
  void setAvailable(bool _available);
  void setId(int _id);
};

#endif
