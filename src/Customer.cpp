#include "doof/Customer.h"
#include "doof/Restaurant.h"

extern Util util;
extern DB db;

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
  vector<Order> orders = db.getOrdersByCustomerId(Customer::getId());
  delete currentorder;
  currentorder = new Order(orders[0]);
  return currentorder;
}

void Customer::displayCurrentOrder() {
  vector<Order> orders = db.getOrdersByCustomerId(Customer::getId());
  // potentially replace this with a separate checker function
  if (orders.empty()) {
    cout << util.colors[COLOR_RED] << "No current order found." << util.colors[COLOR_DEFAULT] << "\n";
    return;
  }

  currentorder = new Order(orders[0]);
  string orderStatusStr;
  switch (currentorder->getStatus()) {
  case ORDER_STATUS_PENDING:
    orderStatusStr = "Pending";
    break;
  case ORDER_STATUS_PROCESSING:
    orderStatusStr = "Processing";
    break;
  case ORDER_STATUS_DISPATCHED:
    orderStatusStr = "Dispatched";
    break;
  }

  cout << util.colors[COLOR_BLUE] << "\n--- Current Order Details ---\n" << util.colors[COLOR_DEFAULT];
  cout << "Order ID: " << currentorder->getId() << "\n";
  cout << "Restaurant ID: " << currentorder->getRestaurantId() << "\n";
  cout << "Order Status: " << util.colors[COLOR_YELLOW] << orderStatusStr << util.colors[COLOR_DEFAULT] << "\n";

  cout << "\nItems in Order:\n";
  cout << left << setw(20) << "Food Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
  cout << string(40, '-') << endl;

  double totalCost = 0.0;

  for (const auto& item : currentorder->getItems()) {
    const Food& food = item.getCartItemFood();
    double itemCost = item.getPrice();
    totalCost += itemCost;

    cout << left << setw(20) << food.getName() << setw(10) << item.getQuantity() << setw(10) << fixed << setprecision(2) << food.getPrice() << endl;
  }

  cout << string(40, '-') << endl;
  cout << "Total Cost: " << util.colors[COLOR_GREEN] << fixed << setprecision(2) << totalCost << util.colors[COLOR_DEFAULT] << "\n\n";
}

bool Customer::hasOngoingOrder() const {
  vector<Order> orders = db.getOrdersByCustomerId(Customer::getId());
  return !orders.empty();
}










