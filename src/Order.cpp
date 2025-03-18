#include "doof/Order.h"

Order::Order() {}

Order::Order(int o_id, int r_id, int c_id, OrderStatus stat) {
  id = o_id;
  restaurantID = r_id;
  customerId = c_id;
  status = stat;
}

Order::~Order() {}

int Order::getId() const {
  return id;
}
void Order::setId(int _id) {
  id = _id;
}

vector<CartItem> Order::getOrder() const {
  return items;
}

void Order::addtoOrder(CartItem item) {
  items.push_back(item);
}

void Order::removefromOrder(int index) {
  items.erase(items.begin() + index - 1);
}

float Order::calculateTotal() {
  float price = 0;
  for (int i = 0; i < items.size(); i++) {
    price += items[i].getCartItemFood().getPrice() * items[i].getCartItemQuantity();
  }
  return price;
}

void Order::markAsPending() {
  status = ORDER_STATUS_PENDING;
}

void Order::markAsProcessing() {
  status = ORDER_STATUS_PROCESSING;
}

void Order::markAsDelivered() {
  status = ORDER_STATUS_DELIVERED;
}

int Order::getRestaurantId() const {
  return restaurantID;
}

void Order::setRestaurantId(int id) {
  restaurantID = id;
}

int Order::getCustomerId() const {
  return customerId;
}
void Order::setCustomerId(int id) {
  customerId = id;
}

const vector<CartItem>& Order::getItems() const {
  return items;
}
void Order::setItems(vector<CartItem> _items) {
  items = _items;
}

OrderStatus Order::getStatus() const {
  return status;
}