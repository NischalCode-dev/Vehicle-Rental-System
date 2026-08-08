#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User();
    User(int id, const std::string& name, const std::string& email,
         const std::string& phone, const std::string& username,
         const std::string& password, const std::string& role);

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;
    int getLoyaltyPoints() const;
    std::string getMembershipLevel() const;
    double getTotalSpent() const;
    int getTotalRentals() const;
    int getCompletedRentals() const;
    int getCancelledRentals() const;
    double getAverageRating() const;

    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setPassword(const std::string& password);
    void setUsername(const std::string& username);
    void setRole(const std::string& role);
    void addLoyaltyPoints(int points);
    void setMembershipLevel(const std::string& membership);
    void addToTotalSpent(double amount);
    void incrementRentals();
    void incrementCompletedRentals();
    void incrementCancelledRentals();
    void setAverageRating(double rating);

protected:
    int id;
    std::string name;
    std::string email;
    std::string phone;
    std::string username;
    std::string password;
    std::string role;
    int loyaltyPoints;
    std::string membershipLevel;
    double totalSpent;
    int totalRentals;
    int completedRentals;
    int cancelledRentals;
    double averageRating;
};

#endif
