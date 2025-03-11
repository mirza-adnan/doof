#ifndef CARTITEM_H
#define CARTITEM_H

#include <iostream>
#include "doof/Food.h"
using namespace std;

class CartItem{
    private:
        Food* food;
        int quantity;
        
    public:
        CartItem();

        //getters
        Food* getCartItemFood();

        int getCartItemQuantity();

        //setters
        void setCartItem(Food* fd);

        void incrementQuantity();

        void incrementQuantity(int inc);
};

#endif