#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <iostream>
#include <string>
#include <vector>
#include "doof/Food.h"
#include "doof/User.h"
#include "doof/Order.h"
#include "doof/Util.h"
using namespace std;


class Restaurant;


class Customer : public User {
private:
  Order* currentorder;
  vector<Order> orderHistory;
  Restaurant* selectedRestaurant;
  vector<CartItem> cart;

public:
  Customer();
  Customer(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr);
  ~Customer();

  void addtoHistory();

  Restaurant& getSelectedRestaurant();
  void setSelectedRestaurant(Restaurant* res);

  const vector<CartItem>& getCart() const;
  void addToCart(CartItem item);
  void clearCart();
  void displayCart();
  bool isCartEmpty() const;

  void setCurrentOrder(Order* order);
  const Order* getCurrentOrder();
};

#endif