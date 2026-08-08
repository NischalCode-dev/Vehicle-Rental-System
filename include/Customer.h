#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
public:
    Customer();
    Customer(int id, const std::string& name, const std::string& email,
             const std::string& phone, const std::string& username,
             const std::string& password);
};

#endif
