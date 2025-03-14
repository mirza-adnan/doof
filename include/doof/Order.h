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
  int restaurantID;
  int userID;
  vector<CartItem> items;
  OrderStatus status;
public:
  Order();

  ~Order();

  //getters
  vector<CartItem> getOrder() const;

  void addtoOrder(CartItem item);

  void removefromOrder(int index);

  float calculateTotal();

  void markAsPending();

  void markAsProcessing();

  void markAsDelivered();
};

#endif