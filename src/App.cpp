#include "doof/App.h"

extern Util util;
extern DB db;

App::App() {
  user = nullptr;
  db.createTables();
  db.getRestaurants();

  screen = SCREEN_ROLE_SELECTION;
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

    case SCREEN_CUSTOMER_MAIN_MENU: {
      App::handleCustomerMainMenu();
      break;
    }

    case SCREEN_CUSTOMER_EXPLORE_RESTAURANTS: {
      App::handleExploreRestaurants();
      break;
    }

    case SCREEN_CUSTOMER_SELECTED_RESTAURANT: {
      App::handleSelectedRestaurant();
      break;
    }

    case SCREEN_CUSTOMER_CART: {
      App::handleCustomerCart();
      break;
    }

    default: {
      screen = SCREEN_EXIT;
      break;
    }
    }
    cin.ignore(1024, '\n');
    util.clearConsole();
  }
}

void App::handleRoleSelection() {
  util.clearConsole();
  util.printBlue("===== WELCOME TO DOOF =====\n");
  delete user;
  user = nullptr;

  Screen options[] = { SCREEN_RESTAURANT_AUTH, SCREEN_CUSTOMER_AUTH, SCREEN_EXIT };
  int selection;
  do {
    util.printLine("Select your role:\n");
    util.printLine("1. Restaurant\n");
    util.printLine("2. Customer\n");
    util.printLine("3. Exit\n");
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 3);

  screen = options[selection - 1];
  auth.setType(static_cast<AuthType>(selection - 1));
}

void App::handleRestaurantAuth() {
  Screen options[] = { SCREEN_RESTAURANT_REGISTER, SCREEN_RESTAURANT_LOGIN, SCREEN_ROLE_SELECTION, SCREEN_EXIT };
  int selection;
  do {
    util.printTitle();
    util.printBlue("Restaurant Auth\n");
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Go Back\n";
    cout << "4. Exit\n";
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 4);
  screen = options[selection - 1];
}

void App::handleCustomerAuth() {
  Screen options[] = { SCREEN_CUSTOMER_REGISTER, SCREEN_CUSTOMER_LOGIN, SCREEN_ROLE_SELECTION, SCREEN_EXIT };
  int selection;
  do {
    util.printBlue("Customer Authentication\n");
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
  util.printBlue("Customer Registration\n");

  do {
    util.printYellow("Email: ");
    getline(cin, email);

    if (db.customerEmailExists(email)) {
      cout << "A customer with that email already exists.\n";
      string selection;
      do {
        cout << "Would you like to go back to the previous page to login instead? (y/n): ";
        getline(cin, selection);
      } while (selection != "y" && selection != "n");

      if (selection == "y") {
        screen = SCREEN_CUSTOMER_AUTH;
        return;
      }
      else if (selection == "n") {
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
  while (true) {
    util.doWhile(contact, "", "Contact Number: ");
    if (contact.size() != 11) {
      util.printRed("Contact number must be 11 digits.");
    }
    else break;
  }

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
  cout << "\n\n\n***  Restaurant Registration  ***\n";

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
  string password = util.getMaskedPassword();

  string name;
  util.doWhile(name, "", "Restaurant Name: ");

  string contact;
  while (true) {
    util.doWhile(contact, "", "Contact Number: ");
    if (contact.size() != 11) {
      util.printRed("Contact number must be 11 digits.");
    }
    else break;
  }

  string address;
  util.doWhile(address, "", "Address: ");

  int type;
  do {
    cout << "Restaurant Type: \n";
    cout << "1. Fast Food\n";
    cout << "2. Cafe\n";
    cout << "3. Fine Dining\n";
    util.printPointer();
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

  util.printBlue("\nRestaurant Login\n");
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

  string password = util.getMaskedPassword();

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

  util.printBlue("Customer Login\n");
  do {
    util.printYellow("Email: ");
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

void App::handleCustomerMainMenu() {
  Screen options[] = { SCREEN_CUSTOMER_EXPLORE_RESTAURANTS, SCREEN_CUSTOMER_CART, SCREEN_CUSTOMER_CURRENT_ORDER, SCREEN_ROLE_SELECTION };
  int selection;

  cout << "HERE\n";

  do {
    string hello = "Welcome to Doof, " + user->getName() + ". How can we help you today?\n";
    util.printBlue(hello);
    cout << "1. Explore Restaurants\n";
    cout << "2. View Cart\n";
    cout << "3. Current Order\n";
    cout << "4. Logout\n";

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

void App::handleExploreRestaurants() {
  vector<Restaurant> restaurants = db.getRestaurants();
  int count = 1;
  util.printBlue("\nExplore your favorites!\n");
  for (Restaurant& res : restaurants) {
    string line = to_string(count) + ". " + res.getName() + "\n";
    util.printGreen(line);
    cout << "      " << "(" << res.getType() << ")\n";
    count++;
  }

  cout << "\n";

  int selection;
  do {
    util.printLine("1. Select Restaurant\n");
    util.printLine("2. Back\n");
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 2);

  if (selection == 1) {
    do {
      util.printYellow("Restaurant Index: ");
      cin >> selection;
    } while (selection < 1 || selection > restaurants.size());

    Restaurant* selected = new Restaurant(restaurants[selection - 1]);

    ((Customer*)user)->setSelectedRestaurant(selected);
    screen = SCREEN_CUSTOMER_SELECTED_RESTAURANT;
  }
  else if (selection == 2) {
    screen = SCREEN_CUSTOMER_MAIN_MENU;
  }
}

void App::handleSelectedRestaurant() {
  ((Customer*)user)->clearCart();
  cout << "\n";
  vector<Food> menu = ((Customer*)user)->getSelectedRestaurant().getMenu();
  string line = ((Customer*)user)->getSelectedRestaurant().getName() + " Menu\n";
  util.printBlue(line);

  int selection = 0;

  for (int i = 0; i < menu.size(); i++) {
    Food& item = menu[i];
    util.printLine(string(to_string(i + 1)) + string(". "));
    util.printMagenta(item.getName());
    util.printLine(string("    ") + string(to_string(item.getPrice())) + string(" BDT\n"));
  }
  cout << "\n";

  do {
    util.printOptions({ "Select Item", "Show Cart", "Back", "Exit" });
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 4);

  if (selection == 1) {
    CartItem item;
    int choice;
    do {
      util.printYellow("Item Index: ");
      cin >> choice;
    } while (choice < 1 || choice > menu.size());

    item.setCartItem(&menu[choice - 1]);


    do {
      util.printYellow("Quantity: ");
      cin >> choice;
    } while (choice < 1);

    item.setQuantity(choice);
    ((Customer*)user)->addToCart(item);
    util.clearConsole();
    string out = item.getCartItemFood()->getName() + " added.\n\n";
    util.printGreen(out);
  }
  else if (selection == 2) {
    screen = SCREEN_CUSTOMER_CART;
  }
  else if (selection == 3) {
    ((Customer*)user)->clearCart();
    screen = SCREEN_CUSTOMER_EXPLORE_RESTAURANTS;
  }
  else if (selection == 4) {
    screen = SCREEN_EXIT;
  }

}

void App::handleCustomerCart() {
  if (((Customer*)user)->isCartEmpty()) {
    util.printRed("Your cart is empty.\n");
    util.printYellow("Press Enter to return to Customer dashboard...");
    util.pressEnter();
    screen = SCREEN_CUSTOMER_MAIN_MENU;
    return;
  }

  string header = ((Customer*)user)->getName() + "'s Cart\n";
  util.printBlue(header);

  int selection;
  do {
    ((Customer*)user)->displayCart();
    util.printOptions({ "Place Order", "Clear Cart", "Go Back", "Exit" });
    util.printPointer();
    cin >> selection;
  } while (selection < 1 || selection > 4);

  if (selection == 1) {
    Order* order = new Order;
    order->setCustomerId(user->getId());
    order->setRestaurantId(((Customer*)user)->getSelectedRestaurant().getId());
    order->setItems(((Customer*)user)->getCart());
    order->markAsPending();

    ((Customer*)user)->setCurrentOrder(order);

    util.printGreen("Got your order! It'll be at your doorstep in no time.\n");
    util.printYellow("Press Enter to return to Customer dashboard...");
    scanf("%c");
    ((Customer*)user)->setSelectedRestaurant(nullptr);
    screen = SCREEN_CUSTOMER_MAIN_MENU;
  }
  else if (selection == 2) {
    ((Customer*)user)->clearCart();
    util.printGreen("Cart Cleared.\n");
    util.printYellow("Press Enter to return to Customer dashboard...");
    scanf("%c");
    ((Customer*)user)->setSelectedRestaurant(nullptr);
    screen = SCREEN_CUSTOMER_MAIN_MENU;
  }
  else if (selection == 3) {
    screen = SCREEN_CUSTOMER_SELECTED_RESTAURANT;
  }
  else if (selection == 4) {
    screen = SCREEN_EXIT;
  }
}