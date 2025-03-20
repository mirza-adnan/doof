#include "doof/Restaurant.h"

extern DB db;
extern Util util;

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
  cout << util.colors[COLOR_BLUE] << left
    << setw(5) << "No."
    << setw(25) << "Food Name"
    << setw(15) << "Price (BDT)"
    << util.colors[COLOR_DEFAULT] << endl;

  cout << util.colors[COLOR_MAGENTA] << string(50, '=') << util.colors[COLOR_DEFAULT] << endl;

  for (int i = 0; i < menu.size(); i++) {
    Food& item = menu[i];
    cout << left << setw(5) << (i + 1)
      << setw(25) << item.getName()
      << setw(15) << fixed << setprecision(2) << item.getPrice() << endl;
  }

  cout << util.colors[COLOR_MAGENTA] << string(50, '=') << util.colors[COLOR_DEFAULT] << endl;

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
  cout << util.colors[COLOR_BLUE] << left << setw(10) << "Order ID"
    << setw(15) << "Customer ID" << setw(15) << "Status"
    << setw(15) << "Total Price(BDT)" << util.colors[COLOR_DEFAULT] << endl;
  cout << util.colors[COLOR_MAGENTA] << string(70, '=') << util.colors[COLOR_DEFAULT] << endl;

  for (size_t i = 0; i < orders.size(); ++i) {
    Order order = orders[i];

    string status;
    string statusColor = util.colors[COLOR_YELLOW];

    switch (order.getStatus()) {
    case ORDER_STATUS_PENDING:
      status = "Pending";
      statusColor = util.colors[COLOR_YELLOW];
      break;
    case ORDER_STATUS_PROCESSING:
      status = "Processing";
      statusColor = util.colors[COLOR_BLUE];
      break;
    case ORDER_STATUS_DISPATCHED:
      status = "Dispatched";
      statusColor = util.colors[COLOR_MAGENTA];
      break;
    case ORDER_STATUS_DELIVERED:
      status = "Delivered";
      statusColor = util.colors[COLOR_GREEN];
      break;
    default:
      status = "Unknown";
      statusColor = util.colors[COLOR_RED];
    }

    cout << left << setw(10) << order.getId()
      << setw(15) << order.getCustomerId()
      << statusColor << setw(15) << status << util.colors[COLOR_DEFAULT]
      << fixed << setprecision(2) << order.calculateTotal() << "\n";

      const vector<CartItem>& items = order.getItems();
      for (const CartItem& item : items) {
        cout << "    " << util.colors[COLOR_GREEN] << "- "
          << item.getCartItemFood().getName()
          << " x" << item.getCartItemQuantity() << util.colors[COLOR_DEFAULT]
          << " (" << fixed << setprecision(2)
            << item.getPrice() << " BDT)" << "\n";
      }

      cout << "\n";
  }
}



