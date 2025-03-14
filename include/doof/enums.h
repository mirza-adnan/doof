#ifndef ENUMS_H
#define ENUMS_H

#include <iostream>
using namespace std;

enum RestaurantType {
  RESTAURANT_TYPE_FAST_FOOD,
  RESTAURANT_TYPE_CAFE,
  RESTAURANT_TYPE_FINE_DINING,
  RESTAURANT_TYPE_TOTAL
};

istream& operator>>(istream& is, RestaurantType& type);
ostream& operator<<(ostream& os, const RestaurantType& type);

enum AuthType {
  AUTH_TYPE_RESTAURANT,
  AUTH_TYPE_CUSTOMER,
  AUTH_TYPE_NONE
};

enum Screen {
  SCREEN_ROLE_SELECTION,
  SCREEN_EXIT,
  SCREEN_RESTAURANT_AUTH,
  SCREEN_RESTAURANT_REGISTER,
  SCREEN_RESTAURANT_LOGIN,
  SCREEN_RESTAURANT_MAIN_MENU,
  SCREEN_RESTAURANT_ADD_ITEM,
  SCREEN_RESTAURANT_DISPLAY_MENU,
  SCREEN_CUSTOMER_AUTH,
  SCREEN_CUSTOMER_MAIN_MENU,
  SCREEN_CUSTOMER_REGISTER,
  SCREEN_CUSTOMER_LOGIN,
  SCREEN_CUSTOMER_MAIN_MENU,
};

enum Color {
  COLOR_DEFAULT,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_TOTAL
};

enum OrderStatus {
  ORDER_STATUS_PENDING,
  ORDER_STATUS_PROCESSING,
  ORDER_STATUS_DELIVERED,
  ORDER_STATUS_TOTAL
};

#endif