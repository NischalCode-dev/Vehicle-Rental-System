#include "Admin.h"

Admin::Admin() : User() {
    role = "admin";
}

Admin::Admin(int id, const std::string& username, const std::string& password)
    : User(id, "Administrator", "admin@rental.local", "0000000000", username, password, "admin") {}
