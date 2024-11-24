#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
private:
  int id;
  string name;
  string email;
  string contact;
  string address;
  string password;

public:
  User(const string& _name, const string& _email, const string& _contact, const string& _addr, const string& _pass);

  // Getters
  int getId() const;
  string getName() const;
  string getEmail() const;
  string getContact() const;
  string getAddress() const;
  string getPassword() const;

  // Setters
  void setId(const int id);
  void setName(const string& name);
  void setEmail(const string& email);
  void setContact(const string& contact);
  void setAddress(const string& address);
  void setPassword(const string& password);

};


#endif