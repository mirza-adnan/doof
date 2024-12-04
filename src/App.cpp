#include "doof/App.h"

App::App() : auth(db) {
  db.createTables();

  screen = SCREEN_ROLE_SELECTION;
  cout << "***************\n";
  cout << "Welcome to Doof\n";
  cout << "***************\n";
}

void App::init() {
  while (screen != SCREEN_EXIT) {
    switch (screen) {

    case SCREEN_ROLE_SELECTION: {
      App::handleRoleSelection();
      break;
    }

    case SCREEN_RESTAURANT_AUTH: {
      App::handleRestaurantAuth();
      break;
    }

    case SCREEN_RESTAURANT_REGISTER: {
      App::handleRestaurantRegister();
      break;
    }

    default: {
      break;
    }
    }
  }
}

void App::printTitle() {
  cout << "\n     Doof     \n";
}

void App::printPointer() {
  cout << "> ";
}

void App::handleRoleSelection() {
  Screen options[] = { SCREEN_RESTAURANT_AUTH, SCREEN_CUSTOMER_AUTH, SCREEN_EXIT };
  int selection;
  do {
    App::printTitle();
    cout << "Select your role:\n";
    cout << "1. Restaurant\n";
    cout << "2. Customer\n";
    cout << "3. Exit\n";
    App::printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 3);

  screen = options[selection - 1];
  auth.setType(static_cast<AuthType>(selection - 1));
}

void App::handleRestaurantAuth() {
  Screen options[] = { SCREEN_RESTAURANT_REGISTER, SCREEN_RESTAURANT_LOGIN, SCREEN_EXIT };
  int selection;
  do {
    App::printTitle();
    cout << "    Restaurant Auth     \n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    App::printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 3);
  screen = options[selection - 1];
}

void App::handleRestaurantRegister() {
  string email;
  cout << "Email\n";
  App::printPointer();
  cin >> email;

  if (db.restaurantEmailExists(email)) {
    cout << "bad email\n";
  }
  else {
    cout << "unique email\n";
  }
}