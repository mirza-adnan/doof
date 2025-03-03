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
  string password;
  string address;
  string contact;

public:
  User();

  User(const string& _name, const string& _email, const string& _pass, const string& _contact, const string& _addr);

  // getters
  int getId() const;
  string& getName();
  string& getEmail();
  string& getPassword();
  string& getAddress();
  string& getContact();

  // setters
  void setId(const int _id);
  void setName(const string& _name);
  void setEmail(const string& _email);
  void setPassword(const string& _password);
  void setAddress(const string& _addr);
  void setContact(const string& _contact);
};


#endif