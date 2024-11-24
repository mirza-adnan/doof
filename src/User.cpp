#include "doof/User.h"

User::User() {}

User::User(const string& _name, const string& _email, const string& _contact, const string& _addr, const string& _pass) {
  name = _name;
  email = email;
  contact = _contact;
  address = _addr;
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

string User::getContact() const {
  return contact;
}

string User::getAddress() const {
  return address;
}

string User::getPassword() const {
  return password;
}

// setters
void User::setId(int _id) {
  id = _id;
}

void User::setName(const string& _name) {
  name = _name;
}

void User::setEmail(const string& _email) {
  email = _email;
}

void User::setContact(const string& _contact) {
  contact = _contact;
}

void User::setAddress(const string& _address) {
  address = _address;
}

void User::setPassword(const string& _password) {
  password = _password;
}
