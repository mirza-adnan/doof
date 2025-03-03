#ifndef AUTH_H
#define AUTH_H

#include "doof/enums.h"
#include "doof/User.h"
#include "doof/DB.h"
#include "doof/Util.h"
#include "doof/Restaurant.h"
#include "sodium/sodium.h"

class Auth {
private:
  AuthType type;
  DB& db;

  string hashPassword(const string& password) const;
  bool verifyPassword(const string& hashedPassword, const string& password) const;

public:
  Auth(DB& _db);

  // getters
  AuthType getType() const;
  int getUserId() const;

  // setters
  void setType(const AuthType _type);
  void setId(const int _id);

  void registerRestaurant(Restaurant& restaurant);
  Restaurant* loginRestaurant(const string& email, const string& password);
  bool isLoggedIn();
};


#endif