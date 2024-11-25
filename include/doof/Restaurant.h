#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "doof/enums.h"
#include "doof/Food.h"
#include "doof/User.h"

class Restaurant : public User {
private:
  string address;
  string contact;
  RestaurantType type;
  vector<Food*> menu;

public:
  Restaurant();

  Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type);

  ~Restaurant();

  // getters
  RestaurantType getType() const;
  string getAddress() const;
  string getContact() const;

  // setters
  void setType(const RestaurantType& _type);
  void setAddress(const string& _addr);
  void setContact(const string& _contact);
};

#endif