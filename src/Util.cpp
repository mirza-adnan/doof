#include "doof/Util.h"

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

Util util;