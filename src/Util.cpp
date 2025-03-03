#include "doof/Util.h"

Util::Util() {
  if (sodium_init() < 0) {
    cerr << "Failed to initialize libsodium\n";
  }
}

void Util::printTitle() const {
  cout << "\nDoof\n";
}

void Util::printPointer() const {
  cout << "> ";
}

void Util::doWhile(string& str, const string& comp, const string& prompt) const {
  do {
    cout << prompt;
    getline(cin, str);
  } while (str == comp);
}

string Util::hashPassword(const string& password) const {
  char hashedPassword[crypto_pwhash_STRBYTES];

  if (crypto_pwhash_str(
    hashedPassword,
    password.c_str(),
    password.size(),
    crypto_pwhash_OPSLIMIT_INTERACTIVE,
    crypto_pwhash_MEMLIMIT_INTERACTIVE
  ) != 0) {
    throw runtime_error("Error hashing password\n");
  }

  return string(hashedPassword);
}

Util util;