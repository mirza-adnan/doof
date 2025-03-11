#include "doof/Order.h"

Order::Order(){
    price = 0;
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

float Order::calculateTotal(){
    for(auto itr: items){
        price += itr.getCartItemFood()->getPrice();
    }
    return price;
}

// void Order::markAsDelivered(){
//     status = delivered;
// }