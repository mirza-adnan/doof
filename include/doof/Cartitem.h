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

        CartItem(Food* f, int q);

        //getters
        Food* getCartItemFood() const;

        int getCartItemQuantity() const;

        //setters
        void setCartItem(const Food*, const int q);

        void incrementQuantity();
};

#endif