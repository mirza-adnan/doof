#include "doof/User.h"

User::User() {}

User::User(const string& _name, const string& _email, const string& _pass) {
  name = _name;
  email = _email;
  password = _pass;
}

// getters
int User::getId() const {
  return id;
}

string User::getName() const {
  return name;
}

string User::getEmail() const {
  return email;
}

string User::getPassword() const {
  return password;
}

// setters
void User::setId(const int _id) {
  id = _id;
}

void User::setName(const string& _name) {
  name = _name;
}

void User::setEmail(const string& _email) {
  email = _email;
}

void User::setPassword(const string& _password) {
  password = _password;
}
