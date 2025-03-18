#include "doof/Cartitem.h"

CartItem::CartItem() {}

Food* CartItem::getCartItemFood() {
  return this->food;
}

int CartItem::getCartItemQuantity() {
  return this->quantity;
}

void CartItem::setCartItem(Food* fd) {
  this->food = fd;
  this->quantity = 1;
}

void CartItem::incrementQuantity() {
  this->quantity++;
}

void CartItem::incrementQuantity(int inc) {
  this->quantity += inc;
}

int CartItem::getQuantity() {
  return quantity;
}

void CartItem::setQuantity(int _q) {
  quantity = _q;
}

float CartItem::getPrice() {
  return food->getPrice() * quantity;
}


