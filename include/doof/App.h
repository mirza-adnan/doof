#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include "doof/Restaurant.h"
#include "doof/DB.h"
#include "doof/Food.h"
#include "doof/Auth.h"
#include "doof/Util.h"
#include "doof/enums.h"


class App {
private:
  DB db;
  Auth auth;
  Screen screen;

public:
  App();
  void printTitle();
  void printPointer();
  void init();
  void handleRoleSelection();
  void handleRestaurantAuth();
  void handleRestaurantRegister();
};

#endif 