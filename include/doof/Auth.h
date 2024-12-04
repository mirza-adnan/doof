#ifndef AUTH_H
#define AUTH_H

#include "doof/enums.h"
#include "doof/User.h"
#include "doof/DB.h"
#include "doof/Util.h"
#include "doof/Restaurant.h"

class Auth {
private:
  AuthType type;
  User* user;
  DB& db;

public:
  Auth(DB& _db);

  // getters
  AuthType getType() const;
  int getUserId() const;

  // setters
  void setType(const AuthType _type);
  void setId(const int _id);

  void registerRestaurant(const Restaurant& restaurant);
  bool isLoggedIn();
};

#endif