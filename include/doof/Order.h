#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "doof/Food.h"
#include "doof/Cartitem.h"
#include "doof/Customer.h"
#include "doof/Restaurant.h"
#include "doof/enums.h"

class Order{
    private:
        int restaurantID;
        int userID;
        vector<CartItem> items;
        float price;
        OrderStatus status;
    public:
        Order();

        Order(vector<CartItem> items, int restaurantID, int userID);

        ~Order();

        //getters
        vector<CartItem> getOrder() const;

        void addtoOrder(CartItem item);

        void removefromOrder(int index);

        float getTotal();

        void markAsDelivered();
};

#endif