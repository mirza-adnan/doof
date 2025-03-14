#include "doof/Customer.h"
#include "doof/Restaurant.h"


Customer::Customer() {}

Customer::Customer(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr) : User(_name, _email, _pass, _contact, _addr) {}

Customer::~Customer() {
    delete selectedRestaurant;
}

void Customer::addtoHistory() {
    orderHistory.push_back(currentorder);
}

Restaurant& Customer::getSelectedRestaurant() {
    return *selectedRestaurant;
}

void Customer::setSelectedRestaurant(Restaurant* res) {
    selectedRestaurant = res;
}









