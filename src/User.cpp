#include "doof/User.h"

User::User(const string& _name, const string& _email, const string& _contact, const string& _addr, const string& _pass) {
  name = _name;
  email = email;
  contact = _contact;
  address = _addr;
  password = _pass;
}

// Getters
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

// Setters
void User::setId(int id) {
  this->id = id;
}

void User::setName(const string& name) {
  this->name = name;
}

void User::setEmail(const string& email) {
  this->email = email;
}

void User::setContact(const string& contact) {
  this->contact = contact;
}

void User::setAddress(const string& address) {
  this->address = address;
}

void User::setPassword(const string& password) {
  this->password = password;
}
