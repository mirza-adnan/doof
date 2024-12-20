#include "doof/Auth.h"

extern Util util;

Auth::Auth(DB& _db) : db(_db) {
  type = AUTH_TYPE_NONE;
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

void Auth::registerRestaurant(const Restaurant& restaurant) {

}