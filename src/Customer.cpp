#include "doof/Customer.h"

Customer::Customer() {}

Customer::Customer(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr) : User(_name, _email, _pass, _contact, _addr){}

Customer::~Customer(){

}

void Customer::addtoHistory(){
    orderHistory.push_back(currentorder);
}


