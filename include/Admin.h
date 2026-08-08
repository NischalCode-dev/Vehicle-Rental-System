#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin();
    Admin(int id, const std::string& username, const std::string& password);
};

#endif
