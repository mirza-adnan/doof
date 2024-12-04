#include "doof/App.h"

extern Util util;

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
    cin.ignore(1024, '\n');
  }
}

void App::printTitle() {
  cout << "\nDoof\n";
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
    cout << "Restaurant Auth     \n";
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
  bool valid = true;

  do {
    cout << "***Restaurant Register***\n";
    cout << "Email: ";
    getline(cin, email);

    if (db.restaurantEmailExists(email)) {
      cout << "A restaurant with that email already exists.\n";
      char selection;
      do {
        cout << "Would you like to go back to the previous page? (y/n): ";
        cin >> selection;
      } while (selection != 'y' && selection != 'n');

      if (selection == 'y') {
        screen = SCREEN_RESTAURANT_AUTH;
        return;
      }
      else if (selection == 'n') {
        valid = false;
      }
    }
    else {
      valid = true;
    }
  } while (!valid);

  string password;
  util.doWhile(password, "", "Password: ");

  string name;
  util.doWhile(name, "", "Restaurant Name: ");

  string contact;
  util.doWhile(contact, "", "Contact Number: ");

  string address;
  util.doWhile(address, "", "Address: ");

  int type;
  do {
    cout << "Restaurant Type: \n";
    cout << "1. Fast Food\n";
    cout << "2. Cafe\n";
    cout << "3. Fine Dining\n";
    App::printPointer();
    cin >> type;
  } while (type < 1 || type > 3);

  Restaurant res(name, email, password, contact, address, static_cast<RestaurantType>(type));
  auth.registerRestaurant(res);
}