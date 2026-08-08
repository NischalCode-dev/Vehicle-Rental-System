#include "User.h"

User::User() : id(0), name(""), email(""), phone(""), username(""), password(""), role("customer"), loyaltyPoints(0), membershipLevel("BRONZE"), totalSpent(0.0), totalRentals(0), completedRentals(0), cancelledRentals(0), averageRating(0.0) {}

User::User(int id, const std::string& name, const std::string& email,
           const std::string& phone, const std::string& username,
           const std::string& password, const std::string& role)
    : id(id), name(name), email(email), phone(phone), username(username), password(password), role(role), loyaltyPoints(0), membershipLevel("BRONZE"), totalSpent(0.0), totalRentals(0), completedRentals(0), cancelledRentals(0), averageRating(0.0) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPhone() const { return phone; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }
int User::getLoyaltyPoints() const { return loyaltyPoints; }
std::string User::getMembershipLevel() const { return membershipLevel; }
double User::getTotalSpent() const { return totalSpent; }
int User::getTotalRentals() const { return totalRentals; }
int User::getCompletedRentals() const { return completedRentals; }
int User::getCancelledRentals() const { return cancelledRentals; }
double User::getAverageRating() const { return averageRating; }

void User::setName(const std::string& value) { name = value; }
void User::setEmail(const std::string& value) { email = value; }
void User::setPhone(const std::string& value) { phone = value; }
void User::setPassword(const std::string& value) { password = value; }
void User::setUsername(const std::string& value) { username = value; }
void User::setRole(const std::string& value) { role = value; }
void User::addLoyaltyPoints(int points) { if (points > 0) loyaltyPoints += points; }
void User::setMembershipLevel(const std::string& value) { membershipLevel = value; }
void User::addToTotalSpent(double amount) { if (amount > 0.0) totalSpent += amount; }
void User::incrementRentals() { ++totalRentals; }
void User::incrementCompletedRentals() { ++completedRentals; }
void User::incrementCancelledRentals() { ++cancelledRentals; }
void User::setAverageRating(double rating) { averageRating = rating; }
