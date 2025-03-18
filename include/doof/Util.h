#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include "sodium/sodium.h"
#include <cstdlib>
#include <conio.h>
#include "doof/enums.h"

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
  void clearConsole() const;
  void printOptions(vector<string> options) const;
  void pressEnter() const;
};

#endif