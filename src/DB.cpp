#include "doof/DB.h"

DB::DB() {
  if (sqlite3_open("./db/doof.dev.db", &db) != SQLITE_OK) {
    cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
  }
}

DB::~DB() {
  sqlite3_close(db);
}

sqlite3*& DB::getDb() {
  return db;
}

bool DB::execute(const string& sql) const {
  char* errorMessage;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
    cerr << "SQL Error: " << errorMessage << "\n";
    sqlite3_free(errorMessage);
    return false;
  }

  return true;
}

void DB::createTables() {
  DB::execute(
    "CREATE TABLE IF NOT EXISTS Restaurant("
    "r_id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "r_name TEXT NOT NULL,"
    "r_email TEXT UNIQUE NOT NULL,"
    "r_password TEXT NOT NULL,"
    "r_address TEXT,"
    "r_contact TEXT,"
    "r_type INTEGER NOT NULL CHECK (r_type in (0, 1, 2)));"
  );
  cout << "Table created\n";
}

bool DB::insertRestaurant(Restaurant& restaurant) const {
  bool success = true;

  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO Restaurant (r_name, r_email, r_password, r_address, r_contact, r_type) VALUES (?, ?, ?, ?, ?, ?);";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error in preparing restaurant insert statement: " << sqlite3_errmsg(db) << "\n";
    success = false;
    sqlite3_finalize(stmt);

    return success;
  }

  sqlite3_bind_text(stmt, 1, restaurant.getName().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, restaurant.getEmail().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, restaurant.getPassword().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, restaurant.getAddress().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, restaurant.getContact().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 6, static_cast<int>(restaurant.getType()));

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    cerr << "Error executing restaurant insert statement: " << sqlite3_errmsg(db) << "\n";
    success = false;
    sqlite3_finalize(stmt);

    return success;
  }

  const int restaurant_id = static_cast<int>(sqlite3_last_insert_rowid(db));
  restaurant.setId(restaurant_id);

  cout << "Data inserted successfully! Last inserted ID: " << restaurant_id << "\n";

  sqlite3_finalize(stmt);

  return success;
}

void DB::getRestaurants() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT r_id, r_name, r_email, r_password, r_address, r_contact, r_type FROM Restaurant;";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT Restaurant statement: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name = (char*)sqlite3_column_text(stmt, 1);
    string email = (char*)sqlite3_column_text(stmt, 2);
    string password = (char*)sqlite3_column_text(stmt, 3);
    string address = (char*)sqlite3_column_text(stmt, 4);
    string contact = (char*)sqlite3_column_text(stmt, 5);
    RestaurantType type = static_cast<RestaurantType>(sqlite3_column_int(stmt, 6));

    cout << id << "\n";
    cout << name << "\n";
    cout << email << "\n";
  }
}
