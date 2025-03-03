#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "sodium/sodium.h"
using namespace std;

class Util {
public:
  Util();
  void printPointer() const;
  void printTitle() const;
  void doWhile(string& str, const string& comp, const string& prompt) const;
  string hashPassword(const string& password) const;
};

#endif