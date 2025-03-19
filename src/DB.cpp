#include "doof/DB.h"
#include "doof/Restaurant.h"
#include "doof/Customer.h"

class Customer;

DB::DB() {
  if (sqlite3_open("./db/doof.db", &db) != SQLITE_OK) {
    cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
  }

  DB::execute("PRAGMA foreign_keys = ON;");
  DB::execute("PRAGMA encoding = 'UTF-8';");
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

  DB::execute(
    "CREATE TABLE IF NOT EXISTS Food("
    "f_id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "f_name TEXT NOT NULL,"
    "f_price REAL NOT NULL,"
    "r_id INTEGER NOT NULL,"
    "FOREIGN KEY(r_id) REFERENCES Restaurant(r_id),"
    "UNIQUE(f_name, r_id));"
  );

  DB::execute(
    "CREATE TABLE IF NOT EXISTS Customer("
    "c_id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "c_name TEXT NOT NULL,"
    "c_email TEXT UNIQUE NOT NULL,"
    "c_password TEXT NOT NULL,"
    "c_address TEXT,"
    "c_contact TEXT);"
  );

  DB::execute(
    "CREATE TABLE IF NOT EXISTS Orders("
    "o_id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "c_id INTEGER NOT NULL,"
    "r_id INTEGER NOT NULL,"
    "o_status INTEGER NOT NULL CHECK (o_status in (0, 1, 2, 3)),"
    "FOREIGN KEY(c_id) REFERENCES Customer(c_id),"
    "FOREIGN KEY(r_id) REFERENCES Restaurant(r_id)"
    ");"
  );

  DB::execute(
    "CREATE TABLE IF NOT EXISTS OrderItems("
    "oi_id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "o_id INTEGER NOT NULL,"
    "f_id INTEGER NOT NULL,"
    "quantity INTEGER NOT NULL,"
    "FOREIGN KEY(o_id) REFERENCES Orders(o_id),"
    "FOREIGN KEY(f_id) REFERENCES Food(f_id)"
    ");"
  );
}

bool DB::insertOrder(Order& order) {
  sqlite3_stmt* stmt;
  string sql = "INSERT INTO Orders (c_id, r_id, o_status) VALUES (?, ?, ?);";

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  sqlite3_bind_int(stmt, 1, order.getCustomerId());
  sqlite3_bind_int(stmt, 2, order.getRestaurantId());
  sqlite3_bind_int(stmt, 3, static_cast<int>(order.getStatus()));

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }

  int orderId = sqlite3_last_insert_rowid(db);
  order.setId(orderId);
  sqlite3_finalize(stmt);

  // Inserting order items
  sql = "INSERT INTO OrderItems (o_id, f_id, quantity) VALUES (?, ?, ?);";

  for (const auto& item : order.getItems()) {
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      cerr << "Failed to prepare order item statement: " << sqlite3_errmsg(db) << "\n";
      return false;
    }

    sqlite3_bind_int(stmt, 1, orderId);
    sqlite3_bind_int(stmt, 2, item.getCartItemFood().getId());
    sqlite3_bind_int(stmt, 3, item.getQuantity());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
      cerr << "Failed to execute order item insertion: " << sqlite3_errmsg(db) << "\n";
      sqlite3_finalize(stmt);
      return false;
    }

    sqlite3_finalize(stmt);
  }

  return true;
}

vector<Order> DB::getOrdersByCustomerId(int customerId) {
  sqlite3_stmt* stmt;
  std::vector<Order> orders;

  string sql = "SELECT o_id, r_id, o_status FROM Orders WHERE c_id = ? AND o_status IN (0, 1, 2);";

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
    return orders;
  }

  sqlite3_bind_int(stmt, 1, customerId);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int orderId = sqlite3_column_int(stmt, 0);
    int restaurantId = sqlite3_column_int(stmt, 1);
    OrderStatus status = static_cast<OrderStatus>(sqlite3_column_int(stmt, 2));

    Order order(orderId, customerId, restaurantId, status);

    sqlite3_stmt* itemStmt;
    std::string itemSql = "SELECT f_id, quantity FROM OrderItems WHERE o_id = ?;";

    if (sqlite3_prepare_v2(db, itemSql.c_str(), -1, &itemStmt, nullptr) == SQLITE_OK) {
      sqlite3_bind_int(itemStmt, 1, orderId);

      while (sqlite3_step(itemStmt) == SQLITE_ROW) {
        int foodId = sqlite3_column_int(itemStmt, 0);
        int quantity = sqlite3_column_int(itemStmt, 1);
        Food food = DB::getFoodById(foodId);
        CartItem item;
        item.setCartItem(food);
        item.setQuantity(quantity);
        order.addtoOrder(item);
      }
    }
    sqlite3_finalize(itemStmt);

    orders.push_back(order);
  }

  sqlite3_finalize(stmt);
  return orders;
}

vector<Order> DB::getOrdersByRestaurantId(int restaurantId) {
  sqlite3_stmt* stmt;
  std::vector<Order> orders;

  string sql = "SELECT o_id, c_id, o_status FROM Orders WHERE r_id = ? AND o_status != 3;";

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
    return orders;
  }

  sqlite3_bind_int(stmt, 1, restaurantId);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int orderId = sqlite3_column_int(stmt, 0);
    int customerId = sqlite3_column_int(stmt, 1);
    OrderStatus status = static_cast<OrderStatus>(sqlite3_column_int(stmt, 2));

    Order order(orderId, customerId, restaurantId, status);

    sqlite3_stmt* itemStmt;
    std::string itemSql = "SELECT f_id, quantity FROM OrderItems WHERE o_id = ?;";

    if (sqlite3_prepare_v2(db, itemSql.c_str(), -1, &itemStmt, nullptr) == SQLITE_OK) {
      sqlite3_bind_int(itemStmt, 1, orderId);

      while (sqlite3_step(itemStmt) == SQLITE_ROW) {
        int foodId = sqlite3_column_int(itemStmt, 0);
        int quantity = sqlite3_column_int(itemStmt, 1);
        Food food = DB::getFoodById(foodId);
        CartItem item;
        item.setCartItem(food);
        item.setQuantity(quantity);
        order.addtoOrder(item);
      }
    }
    sqlite3_finalize(itemStmt);

    orders.push_back(order);
  }

  sqlite3_finalize(stmt);
  return orders;
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

  cout << "Restaurant inserted successfully! Last inserted ID: " << restaurant_id << "\n";

  sqlite3_finalize(stmt);

  return success;
}

bool DB::insertCustomer(Customer& customer) const {
  bool success = true;

  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO Customer (c_name, c_email, c_password, c_address, c_contact) VALUES (?, ?, ?, ?, ?);";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error in preparing customer insert statement: " << sqlite3_errmsg(db) << "\n";
    success = false;
    sqlite3_finalize(stmt);

    return success;
  }

  sqlite3_bind_text(stmt, 1, customer.getName().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, customer.getEmail().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, customer.getPassword().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, customer.getAddress().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, customer.getContact().c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    cerr << "Error executing customer insert statement: " << sqlite3_errmsg(db) << "\n";
    success = false;
    sqlite3_finalize(stmt);

    return success;
  }

  const int customer_id = static_cast<int>(sqlite3_last_insert_rowid(db));
  customer.setId(customer_id);

  cout << "Customer added to DB. ID: " << customer_id << "\n";

  sqlite3_finalize(stmt);

  return success;
}

vector<Restaurant> DB::getRestaurants() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT r_id, r_name, r_email, r_password, r_address, r_contact, r_type FROM Restaurant;";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT Restaurant statement: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return {};
  }

  vector<Restaurant> result;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name = (char*)sqlite3_column_text(stmt, 1);
    string email = (char*)sqlite3_column_text(stmt, 2);
    string password = (char*)sqlite3_column_text(stmt, 3);
    string address = (char*)sqlite3_column_text(stmt, 4);
    string contact = (char*)sqlite3_column_text(stmt, 5);
    RestaurantType type = static_cast<RestaurantType>(sqlite3_column_int(stmt, 6));

    Restaurant res(id, name, email, password, contact, address, type);
    result.push_back(res);
  }

  return result;
}

void DB::insertFood(Food& food) const {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO Food (f_name, f_price, r_id) VALUES (?, ?, ?);";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing INSERT statement(Food): " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_bind_text(stmt, 1, food.getName().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 2, food.getPrice());
  sqlite3_bind_int(stmt, 3, food.getRestaurantId());

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    cerr << "Error executing INSERT statement(Food): " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return;
  }

  const int foodId = static_cast<int>(sqlite3_last_insert_rowid(db));
  food.setId(foodId);

  cout << "Food inserted successfully with ID: " << foodId << "\n";

  sqlite3_finalize(stmt);
}

Food DB::getFoodById(int foodId) {
  sqlite3_stmt* stmt;
  std::string sql = "SELECT f_name, f_price, r_id FROM Food WHERE f_id = ?;";

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
    return Food();
  }

  sqlite3_bind_int(stmt, 1, foodId);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    double price = sqlite3_column_double(stmt, 1);
    int restaurantId = sqlite3_column_int(stmt, 2);
    sqlite3_finalize(stmt);
    return Food(foodId, name, price, restaurantId);
  }

  sqlite3_finalize(stmt);
  return Food();
}

vector<Food> DB::getMenu(const int restaurantId) const {
  sqlite3_stmt* stmt;
  const char* query = "SELECT f_id, f_name, f_price, r_id FROM Food WHERE r_id = ?;";

  if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT statement(Food): " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return {};
  }

  if (sqlite3_bind_int(stmt, 1, restaurantId) != SQLITE_OK) {
    cerr << "Error binding email parameter: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return {};
  }

  vector<Food> result;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name = (char*)sqlite3_column_text(stmt, 1);
    float price = sqlite3_column_double(stmt, 2);
    int resId = sqlite3_column_int(stmt, 3);


    result.push_back(Food(id, name, price, resId));
  }

  sqlite3_finalize(stmt);

  return result;
}


bool DB::restaurantEmailExists(const string& email) const {
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT r_name FROM Restaurant WHERE r_email = ?;";

  if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT statement(Restaurant): " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
    cerr << "Error binding email parameter: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }

  bool exists = false;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    exists = true;
  }

  sqlite3_finalize(stmt);
  return exists;
}

bool DB::customerEmailExists(const string& email) const {
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT c_name FROM Customer WHERE c_email = ?;";

  if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT statement(Customer): " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
    cerr << "Error binding email parameter: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }

  bool exists = false;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    exists = true;
  }

  sqlite3_finalize(stmt);
  return exists;
}

Restaurant* DB::getRestaurantByEmail(const string& email) const {
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT r_id, r_name, r_email, r_password, r_address, r_contact, r_type FROM Restaurant WHERE r_email = ?;";

  if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT statement(Restaurant): " << sqlite3_errmsg(db) << "\n";
    throw runtime_error("");
  }

  if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
    cerr << "Error binding email parameter: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    throw runtime_error("");
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name = (char*)sqlite3_column_text(stmt, 1);
    string email = (char*)sqlite3_column_text(stmt, 2);
    string password = (char*)sqlite3_column_text(stmt, 3);
    string address = (char*)sqlite3_column_text(stmt, 4);
    string contact = (char*)sqlite3_column_text(stmt, 5);
    RestaurantType type = static_cast<RestaurantType>(sqlite3_column_int(stmt, 6));

    Restaurant* res = new Restaurant(name, email, password, address, contact, type);
    res->setId(id);

    sqlite3_finalize(stmt);

    return res;
  }
  else {
    sqlite3_finalize(stmt);
    throw runtime_error("");
  }
}

Customer* DB::getCustomerByEmail(const string& email) const {
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT c_id, c_name, c_email, c_password, c_address, c_contact FROM Customer WHERE c_email = ?;";

  if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
    cerr << "Error preparing SELECT statement(Customer): " << sqlite3_errmsg(db) << "\n";
    throw runtime_error("");
  }

  if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
    cerr << "Error binding email parameter: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    throw runtime_error("");
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name = (char*)sqlite3_column_text(stmt, 1);
    string email = (char*)sqlite3_column_text(stmt, 2);
    string password = (char*)sqlite3_column_text(stmt, 3);
    string address = (char*)sqlite3_column_text(stmt, 4);
    string contact = (char*)sqlite3_column_text(stmt, 5);

    Customer* customer = new Customer(name, email, password, address, contact);
    customer->setId(id);

    sqlite3_finalize(stmt);

    return customer;
  }
  else {
    sqlite3_finalize(stmt);
    throw runtime_error("");
  }
}

DB db;