#include "doof/Customer.h"
#include "doof/Restaurant.h"

extern Util util;

Customer::Customer() {}

Customer::Customer(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr) : User(_name, _email, _pass, _contact, _addr) {
  currentorder = nullptr;
}

Customer::~Customer() {
  delete selectedRestaurant;
}

void Customer::addtoHistory() {
  orderHistory.push_back(*currentorder);
}

Restaurant& Customer::getSelectedRestaurant() {
  return *selectedRestaurant;
}

void Customer::setSelectedRestaurant(Restaurant* res) {
  selectedRestaurant = res;
}

const vector<CartItem>& Customer::getCart() const {
  return cart;
}

void Customer::addToCart(CartItem item) {
  cart.push_back(item);
}

void Customer::clearCart() {
  cart.clear();
}

void Customer::displayCart() {
  for (int i = 0; i < cart.size(); i++) {
    CartItem& item = cart[i];
    float price = item.getCartItemFood().getPrice() * item.getQuantity();
    util.printLine(string(to_string(i + 1)) + string(". "));
    util.printGreen(item.getCartItemFood().getName());
    util.printLine(string("  -----  ") + to_string(price) + string(" BDT\n"));
  }

  cout << "\n\n";
}

bool Customer::isCartEmpty() const {
  return cart.empty();
}

void Customer::setCurrentOrder(Order* order) {
  currentorder = order;
}

const Order* Customer::getCurrentOrder() {
  return currentorder;
}









