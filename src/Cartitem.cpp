#include "doof/Cartitem.h"

CartItem::CartItem() {}

Food CartItem::getCartItemFood() const {
  return this->food;
}

int CartItem::getCartItemQuantity() const {
  return this->quantity;
}

void CartItem::setCartItem(Food fd) {
  this->food = fd;
  this->quantity = 1;
}

void CartItem::incrementQuantity() {
  this->quantity++;
}

void CartItem::incrementQuantity(int inc) {
  this->quantity += inc;
}

int CartItem::getQuantity() const {
  return quantity;
}

void CartItem::setQuantity(int _q) {
  quantity = _q;
}

float CartItem::getPrice() const {
  return food.getPrice() * quantity;
}


