#include "Coupon.h"

Coupon::Coupon() : id(0), code(""), discountType("PERCENT"), discountValue(0.0), minAmount(0.0), expiryDate(), maxUsage(0), currentUsage(0), active(false) {}

Coupon::Coupon(int id, const std::string& code, const std::string& discountType,
               double discountValue, double minAmount, const Date& expiryDate,
               int maxUsage, int currentUsage, bool active)
    : id(id), code(code), discountType(discountType), discountValue(discountValue),
      minAmount(minAmount), expiryDate(expiryDate), maxUsage(maxUsage), currentUsage(currentUsage), active(active) {}

int Coupon::getId() const { return id; }
std::string Coupon::getCode() const { return code; }
std::string Coupon::getDiscountType() const { return discountType; }
double Coupon::getDiscountValue() const { return discountValue; }
double Coupon::getMinAmount() const { return minAmount; }
Date Coupon::getExpiryDate() const { return expiryDate; }
int Coupon::getMaxUsage() const { return maxUsage; }
int Coupon::getCurrentUsage() const { return currentUsage; }
bool Coupon::isActive() const { return active; }

void Coupon::setActive(bool value) { active = value; }
void Coupon::incrementUsage() { ++currentUsage; }

bool Coupon::isValidFor(double amount, const Date& today) const {
    if (!active) return false;
    if (currentUsage >= maxUsage) return false;
    if (today > expiryDate) return false;
    return amount >= minAmount;
}

double Coupon::calculateDiscount(double amount) const {
    if (!isValidFor(amount, Date::parse("01-01-2099"))) {
        return 0.0;
    }
    if (discountType == "FIXED") {
        return std::min(amount, discountValue);
    }
    return amount * (discountValue / 100.0);
}
