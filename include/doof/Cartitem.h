#ifndef CARTITEM_H
#define CARTITEM_H

#include <iostream>
#include "doof/Food.h"
using namespace std;

class CartItem {
private:
  Food food;
  int quantity;

public:
  CartItem();

  //getters
  Food getCartItemFood() const;
  int getQuantity() const;

  int getCartItemQuantity() const;

  //setters
  void setCartItem(Food fd);
  void setQuantity(int _q);


  void incrementQuantity();

  void incrementQuantity(int inc);

  float getPrice() const;
};

#endif