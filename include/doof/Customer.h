#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
#include "doof/Food.h"
#include "doof/User.h"
#include "doof/Order.h"
using namespace std;

class Customer : public User {
private:
    Order currentorder;
    vector<Order> orderHistory;


public:
    Customer();

    Customer(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr);

    ~Customer();

    void addtoHistory();
};

#endif