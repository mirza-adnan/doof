#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "doof/Food.h"
#include "doof/Cartitem.h"
#include "doof/Customer.h"
#include "doof/Restaurant.h"

class Order{
    private:
        vector<CartItem> items;
        float price;
        //OrderStatus status;
    public:
        Order();

        //getters
        vector<CartItem> getOrder() const;

        void addtoOrder(CartItem item);

        void removefromOrder();

        //void markAsDelivered();
};

#endif