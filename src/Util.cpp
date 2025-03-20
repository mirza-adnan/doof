#include "doof/Util.h"

Util::Util() : colors(vector<string>(COLOR_TOTAL)) {
  colors[COLOR_DEFAULT] = "\033[0m";
  colors[COLOR_RED] = "\033[38;5;160m";
  colors[COLOR_GREEN] = "\033[38;5;64m";
  colors[COLOR_YELLOW] = "\033[38;5;136m";
  colors[COLOR_BLUE] = "\033[38;5;33m";
  colors[COLOR_MAGENTA] = "\033[38;5;125m";
}

void Util::printTitle() const {
  cout << "Doof\n";
}

void Util::printPointer() const {
  Util::printGreen("> ");
}

void Util::doWhile(string& str, const string& comp, const string& prompt) const {
  do {
    Util::printYellow(prompt);
    getline(cin, str);
  } while (str == comp);
}

string Util::getMaskedPassword() const {
  string password;
  char ch;
  Util::printYellow("Password: ");
  while ((ch = _getch()) != 13) {
    if (ch == 8) {
      if (!password.empty()) {
        password.pop_back();
        cout << "\b \b";
      }
    }
    else {
      password.push_back(ch);
      cout << "*";
    }
  }
  cout << "\n";

  return password;
}

void Util::printRed(const string& str) const {
  cout << colors[COLOR_RED] << str << colors[COLOR_DEFAULT];
}

void Util::printBlue(const string& str) const {
  cout << colors[COLOR_BLUE] << str << colors[COLOR_DEFAULT];
}

void Util::printGreen(const string& str) const {
  cout << colors[COLOR_GREEN] << str << colors[COLOR_DEFAULT];
}

void Util::printYellow(const string& str) const {
  cout << colors[COLOR_YELLOW] << str << colors[COLOR_DEFAULT];
}

void Util::printMagenta(const string& str) const {
  cout << colors[COLOR_MAGENTA] << str << colors[COLOR_DEFAULT];
}

void Util::printLine(const string& str) const {
  cout << colors[COLOR_DEFAULT] << str;
}

void Util::printBanner() const {
  cout << "  _____              ______ \n";
  cout << " |  __ \\            |  ____|\n";
  cout << " | |  | | ___   ___ | |__   \n";
  cout << " | |  | |/ _ \\ / _ \\|  __|  \n";
  cout << " | |__| | (o) | (o) | |     \n";
  cout << " |_____/ \\___/ \\___/|_|     \n";
  cout << "\n\n";
}

void Util::clearConsole() const {
  system("clear");
}

void Util::printOptions(vector<string> options) const {
  for (int i = 0; i < options.size(); i++) {
    cout << i + 1 << ". " << options[i] << "\n";
  }
}

void Util::pressEnter() const {
  while (getchar() != '\n');
}

Util util;