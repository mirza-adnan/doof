#include "doof/App.h"

extern Util util;
extern DB db;

App::App(){
  user = nullptr;
  db.execute("DROP TABLE Food;");
  db.createTables();
  db.getRestaurants();

  screen = SCREEN_ROLE_SELECTION;
  cout << "***************\n";
  cout << "Welcome to Doof\n";
  cout << "***************\n";
}

App::~App() {
  delete user;
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

    case SCREEN_RESTAURANT_LOGIN: {
      App::handleRestaurantLogin();
      break;
    }

    case SCREEN_RESTAURANT_MAIN_MENU: {
      App::handleRestaurantMainMenu();
      break;
    }

    case SCREEN_RESTAURANT_ADD_ITEM: {
      App::handleRestaurantAddItem();
      break;
    }

    case SCREEN_RESTAURANT_DISPLAY_MENU: {
      App::handleRestaurantDisplayMenu();
      break;
    }

    case SCREEN_CUSTOMER_AUTH: {
      App::handleCustomerAuth();
      break;
    }

    case SCREEN_CUSTOMER_REGISTER: {
      App::handleCustomerRegister();
      break;
    }

    case SCREEN_CUSTOMER_LOGIN: {
      App::handleCustomerLogin();
      break;
    }

    default: {
      screen = SCREEN_EXIT;
      break;
    }
    }
    cin.ignore(1024, '\n');
    // cout << "\x1B[2J\x1B[H";
  }
}

void App::printTitle() {
  cout << "Doof\n";
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
    util.printPointer();
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

void App::handleCustomerAuth() {
  Screen options[] = { SCREEN_CUSTOMER_REGISTER, SCREEN_CUSTOMER_LOGIN, SCREEN_ROLE_SELECTION, SCREEN_EXIT };
  int selection;
  do {
    util.printTitle();
    cout << "Customer Auth\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Go Back\n";
    cout << "4. Exit\n";
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 4);
  screen = options[selection - 1];
}

void App::handleCustomerRegister() {
  string email;
  bool valid = true;
  cout << "\n\n\n***  Customer Registration  ***\n";


  do {
    cout << "Emaill: ";
    getline(cin, email);


    if (db.customerEmailExists(email)) {
      cout << "A customer with that email already exists.\n";
      char selection;
      do {
        cout << "Would you like to go back to the previous page to login instead? (y/n): ";
        cin >> selection;
      } while (selection != 'y' && selection != 'n');


      if (selection == 'y') {
        screen = SCREEN_CUSTOMER_AUTH;
        return;
      }
      else if (selection == 'n') {
        valid = false;
      }
    }
    else {
      valid = true;
    }
  } while (!valid || email == "");


  string password = util.getMaskedPassword();


  string name;
  util.doWhile(name, "", "Name: ");


  string contact;
  util.doWhile(contact, "", "Contact Number: ");


  string address;
  util.doWhile(address, "", "Address: ");


  Customer* customer = new Customer(name, email, password, contact, address);
  auth.registerCustomer(*customer);


  user = customer;
  screen = SCREEN_CUSTOMER_MAIN_MENU;


  cout << "Press Enter to continue...";
}

void App::handleRestaurantRegister() {
  string email;
  bool valid = true;
  cout << "***Restaurant Register***\n";

  do {
    cout << "Email: ";
    getline(cin, email);

    if (db.restaurantEmailExists(email)) {
      cout << "A restaurant with that email already exists.\n";
      char selection;
      do {
        cout << "Would you like to go back to the previous page to login instead? (y/n): ";
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
  } while (!valid || email == "");

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

  Restaurant* res = new Restaurant(name, email, password, contact, address, static_cast<RestaurantType>(type - 1));
  auth.registerRestaurant(*res);

  user = res;
  db.getRestaurants();
  screen = SCREEN_RESTAURANT_MAIN_MENU;
}

void App::handleRestaurantLogin() {
  string email;
  bool validEmail;

  cout << "***Restaurant Login***\n";
  do {
    cout << "Email: ";
    getline(cin, email);

    if (email == "") {
      continue;
    }

    if (!db.restaurantEmailExists(email)) {
      cout << "There does not seem to be a restaurant with that email.\n";

      char selection;
      do {
        cout << "Would you like to go back? (y/n): ";
        cin >> selection;
      } while (selection != 'y' && selection != 'n');

      if (selection == 'y') {
        screen = SCREEN_RESTAURANT_AUTH;
        return;
      }
      else if (selection == 'n') {
        validEmail = false;
      }
    }
    else {
      validEmail = true;
    }
  } while (!validEmail || email == "");

  string password;
  util.doWhile(password, "", "Password: ");

  try {
    user = auth.loginRestaurant(email, password);
    if (!user) {
      screen = SCREEN_RESTAURANT_AUTH;
      throw runtime_error("");
    }
    else {
      ((Restaurant*)user)->setMenu(db.getMenu(user->getId()));
      cout << "Logged in successfully\n";
      cout << "Press Enter to continue...";
      screen = SCREEN_RESTAURANT_MAIN_MENU;
    }
  }
  catch (exception& e) {
    cout << "Failed to fetch restaurant with that email\n";
    screen = SCREEN_RESTAURANT_AUTH;
  }
}

void App::handleCustomerLogin() {
  string email;
  bool validEmail;


  cout << "\n\n\n***  Customer Login  ***\n";
  do {
    cout << "Email: ";
    getline(cin, email);


    if (email == "") {
      continue;
    }


    if (!db.customerEmailExists(email)) {
      cout << "There does not seem to be a customer with that email.\n";


      char selection;
      do {
        cout << "Would you like to go back? (y/n): ";
        cin >> selection;
      } while (selection != 'y' && selection != 'n');


      if (selection == 'y') {
        screen = SCREEN_CUSTOMER_AUTH;
        return;
      }
      else if (selection == 'n') {
        validEmail = false;
      }
    }
    else {
      validEmail = true;
    }
  } while (!validEmail || email == "");


  string password = util.getMaskedPassword();


  try {
    user = auth.loginCustomer(email, password);
    if (!user) {
      screen = SCREEN_RESTAURANT_AUTH;
      throw runtime_error("");
    }
    else {
      cout << "Logged in successfully.\n";
      cout << "Press Enter to continue...";
      screen = SCREEN_CUSTOMER_MAIN_MENU;
    }
  }
  catch (exception& e) {
    cout << "Failed to fetch restaurant with that email\n";
    screen = SCREEN_RESTAURANT_AUTH;
  }
}

void App::handleRestaurantMainMenu() {
  Screen options[] = { SCREEN_RESTAURANT_ADD_ITEM, SCREEN_RESTAURANT_DISPLAY_MENU };
  int selection;

  do {
    cout << "\n" << user->getName();
    cout << " Main Menu\n";
    cout << "1. Add Item to Menu\n";
    cout << "2. Display Menu\n";
    cout << "3. View Orders\n";
    cout << "4. Dispatch Current Order\n";

    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 4);

  screen = options[selection - 1];

}

void App::handleRestaurantAddItem() {
  string name;
  util.doWhile(name, "", "Item Name: ");

  float price;
  do {
    cout << "Price: ";
    cin >> price;
  } while (price <= 0);

  Food food(name, price, user->getId());
  ((Restaurant*)user)->addToMenu(food);

  cout << "Item successfully added to the menu!\n";
  screen = SCREEN_RESTAURANT_MAIN_MENU;
}

void App::handleRestaurantDisplayMenu() {
  ((Restaurant*)user)->displayMenu();
  screen = SCREEN_RESTAURANT_MAIN_MENU;
}