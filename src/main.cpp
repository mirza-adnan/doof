#include <windows.h>
#include <iostream>
#include "doof/Restaurant.h"
#include "doof/DB.h"
#include "doof/App.h"
#include "doof/Util.h"

using namespace std;
using std::byte;

void enableAnsiEscapeCodes() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
}

int main() {
  enableAnsiEscapeCodes();

  App app;
  app.init();

  return 0;
}