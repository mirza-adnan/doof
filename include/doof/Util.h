#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "sodium/sodium.h"
#include <conio.h>
#include <vector>
#include "doof/enums.h"
#include <string>
using namespace std;

class Util {
private:
  vector<string> colors;

public:
  Util();
  void printPointer() const;
  void printTitle() const;
  void doWhile(string& str, const string& comp, const string& prompt) const;
  string getMaskedPassword() const;
  void printRed(const string& str) const;
  void printBlue(const string& str) const;
  void printGreen(const string& str) const;
  void printYellow(const string& str) const;
  void printMagenta(const string& str) const;
  void printLine(const string& str) const;
  void printBanner() const;
};

#endif