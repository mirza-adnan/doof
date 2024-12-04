#ifndef UTIL_H
#define UTIL_H

#include <iostream>
using namespace std;

class Util {
public:
  void printPointer() const;
  void printTitle() const;
  void doWhile(string& str, const string& comp, const string& prompt) const;
};

#endif