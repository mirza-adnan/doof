#include "doof/Restaurant.h"

extern DB db;

Restaurant::Restaurant() {}

Restaurant::Restaurant(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_name, _email, _pass, _contact, _addr) {
  type = _type;
}

Restaurant::Restaurant(int _id, const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr, RestaurantType _type) : User(_id, _name, _email, _pass, _contact, _addr) {
  type = _type;
}

Restaurant::~Restaurant() {}

// getters
RestaurantType Restaurant::getType() const {
  return type;
}

const vector<Food>& Restaurant::getMenu() {
  Restaurant::setMenu(db.getMenu(Restaurant::getId()));
  return menu;
}

// setters
void Restaurant::setType(const RestaurantType& _type) {
  type = _type;
}

void Restaurant::setMenu(vector<Food> _menu) {
  menu = _menu;
}

void Restaurant::addToMenu(Food item) {
  db.insertFood(item);
  menu.push_back(item);
  cout << item.getName() << "\n";
}

void Restaurant::displayMenu() {
  for (int i = 0; i < menu.size(); i++) {
    printf("%d. \t %s \t %.2f BDT\n", i + 1, menu[i].getName().c_str(), menu[i].getPrice());
  }
}

const vector<Order> Restaurant::getOrders() {
  orders = db.getOrdersByRestaurantId(Restaurant::getId());
  return orders;
}
void Restaurant::addOrder(Order order) {
  orders.push_back(order);
}

void Restaurant::displayOrders() {
  orders = db.getOrdersByRestaurantId(Restaurant::getId());
  cout << left << setw(10) << "Order ID" << setw(15) << "Customer ID" << setw(15)
    << "Restaurant ID" << setw(15) << "Status" << setw(15) << "Total Price" << endl;
  cout << string(70, '=') << endl;

  for (size_t i = 0; i < orders.size(); ++i) {
    Order order = orders[i];

    // Display basic order details
    string status;
    switch (order.getStatus()) {
    case ORDER_STATUS_PENDING: status = "Pending"; break;
    case ORDER_STATUS_PROCESSING: status = "Processing"; break;
    case ORDER_STATUS_DELIVERED: status = "Delivered"; break;
    default: status = "Unknown";
    }

    cout << left << setw(10) << order.getId()
      << setw(15) << order.getCustomerId()
      << setw(15) << order.getRestaurantId()
      << setw(15) << status
      << fixed << setprecision(2) << order.calculateTotal() << endl;

    const vector<CartItem>& items = order.getItems();
    for (const CartItem& item : items) {
      cout << "    - " << item.getCartItemFood().getName()
        << " x" << item.getCartItemQuantity()
        << " ($" << fixed << setprecision(2) << item.getPrice() << ")" << endl;
    }

    cout << endl;
  }
}


