#include "Customer.h"

Customer::Customer() : User() {
    role = "customer";
}

Customer::Customer(int id, const std::string& name, const std::string& email,
                   const std::string& phone, const std::string& username,
                   const std::string& password)
    : User(id, name, email, phone, username, password, "customer") {}
