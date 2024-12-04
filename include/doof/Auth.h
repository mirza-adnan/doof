#ifndef AUTH_H
#define AUTH_H

#include "doof/enums.h"
#include "doof/DB.h"

class Auth {
private:
  AuthType type;
  int userId;
  DB& db;

public:
  Auth(DB& _db);

  // getters
  AuthType getType() const;
  int getUserId() const;

  // setters
  void setType(const AuthType _type);
  void setId(const int _id);

  void registerRestaurant();
  bool isLoggedIn();
};

#endif