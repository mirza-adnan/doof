#include "doof/Order.h"

Order::Order(){}

Order::~Order(){
    items.clear();
}

vector<CartItem> Order::getOrder() const{
    return items;
}

void Order::addtoOrder(CartItem item){
    items.push_back(item);
}

void Order::removefromOrder(int index){
    items.erase(items.begin()+index-1);
}

float Order::calculateTotal(){
    float price = 0;
    for(int i=0; i<items.size(); i++){
        price += items[i].getCartItemFood()->getPrice() * items[i].getCartItemQuantity();
    }
    return price;
}

void Order::markAsPending(){
    status = ORDER_STATUS_PENDING;
}

void Order::markAsProcessing(){
    status = ORDER_STATUS_PROCESSING;
}

void Order::markAsDelivered(){
    status = ORDER_STATUS_DELIVERED;
}