#include "doof/Auth.h"

extern Util util;
extern DB db;

Auth::Auth() {
  type = AUTH_TYPE_NONE;
  if (sodium_init() < 0) {
    cerr << "Failed to initialize libsodium\n";
  }
}

AuthType Auth::getType() const {
  return type;
}

void Auth::setType(const AuthType _type) {
  type = _type;
}

bool Auth::isLoggedIn() {
  return type != AUTH_TYPE_NONE;
}

void Auth::registerRestaurant(Restaurant& restaurant) {
  cout << "Password: " << restaurant.getPassword() << "\n";
  cout << "hashed: " << util.hashPassword(restaurant.getPassword()) << "\n";
  restaurant.setPassword(util.hashPassword(restaurant.getPassword()));
  cout << "hashed2: " << restaurant.getPassword() << "\n";
  db.insertRestaurant(restaurant);
  type = AUTH_TYPE_RESTAURANT;
}

void Auth::registerCustomer(Customer& customer) {
  customer.setPassword(Auth::hashPassword(customer.getPassword()));
  db.insertCustomer(customer);
  type = AUTH_TYPE_CUSTOMER;
}

Restaurant* Auth::loginRestaurant(const string& email, const string& password) {
  Restaurant* res = db.getRestaurantByEmail(email);
  if (Auth::verifyPassword(res->getPassword(), password)) {
    type = AUTH_TYPE_RESTAURANT;
    return res;
  }
  else {
    cout << "The password you entered is not correct\n";
    return nullptr;
  }
}

string Auth::hashPassword(const string& password) const {
  char hashedPassword[crypto_pwhash_STRBYTES];

  if (crypto_pwhash_str(
    hashedPassword,
    password.c_str(),
    password.size(),
    crypto_pwhash_OPSLIMIT_INTERACTIVE,
    crypto_pwhash_MEMLIMIT_INTERACTIVE
  ) != 0) {
    throw runtime_error("Error hashing password\n");
  }

  return string(hashedPassword);
}

bool Auth::verifyPassword(const string& hashedPassword, const string& password) const {
  return crypto_pwhash_str_verify(
    hashedPassword.c_str(),
    password.c_str(),
    password.length()
  ) == 0;
}