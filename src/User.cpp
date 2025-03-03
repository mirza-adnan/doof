#include "doof/User.h"

User::User() {}

User::User(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr) {
  name = _name;
  email = _email;
  password = _pass;
  contact = _contact;
  address = _addr;
}

// getters
int User::getId() const {
  return id;
}

string& User::getName() {
  return name;
}

string& User::getEmail() {
  return email;
}

string& User::getPassword() {
  return password;
}

string& User::getAddress() {
  return address;
}

string& User::getContact() {
  return contact;
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

void User::setAddress(const string& _addr) {
  address = _addr;
}

void User::setContact(const string& _contact) {
  contact = _contact;
}
