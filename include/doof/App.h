#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include "doof/User.h"
#include "doof/Restaurant.h"
#include "doof/DB.h"
#include "doof/Food.h"
#include "doof/Auth.h"
#include "doof/Util.h"
#include "doof/enums.h"
#include "sodium/sodium.h"
#include <conio.h>


class App {
private:
  Auth auth;
  Screen screen;
  User* user;

public:
  App();
  ~App();
  void printTitle();
  void printPointer();
  void init();
  void handleRoleSelection();
  void handleRestaurantAuth();
  void handleRestaurantRegister();
  void handleRestaurantLogin();
  void handleRestaurantMainMenu();
  void handleRestaurantAddItem();
  void handleRestaurantDisplayMenu();
};

#endif 