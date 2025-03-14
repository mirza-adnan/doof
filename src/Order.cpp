#include "doof/Order.h"

Order::Order(){}

Order::Order(vector<CartItem> items, int restaurantID, int userID){
    this->items = items;
    this->restaurantID = restaurantID;
    this->userID = userID;
    this->price = 0;
    for(auto itr: items){
        this->price += itr.getCartItemFood()->getPrice();
    }
    status = ORDER_STATUS_PENDING;
}

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

float Order::getTotal(){
    return price;
}

void Order::markAsDelivered(){
    status = ORDER_STATUS_DELIVERED;
}