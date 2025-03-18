#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "doof/Food.h"
#include "doof/Cartitem.h"
#include <vector>
#include "doof/enums.h"
using namespace std;


class Order {
private:
  int id;
  int restaurantID;
  int customerId;
  vector<CartItem> items;
  OrderStatus status;
public:
  Order();

  Order(int o_id, int r_id, int c_id, OrderStatus stat);

  ~Order();

  int getId() const;
  void setId(int _id);

  vector<CartItem> getOrder() const;

  void addtoOrder(CartItem item);

  void removefromOrder(int index);

  float calculateTotal();

  void markAsPending();

  void markAsProcessing();

  void markAsDelivered();

  int getRestaurantId() const;
  void setRestaurantId(int id);

  int getCustomerId() const;
  void setCustomerId(int id);

  const vector<CartItem>& getItems() const;
  void setItems(vector<CartItem> _items);

  OrderStatus getStatus() const;
};

#endif