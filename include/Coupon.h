#ifndef COUPON_H
#define COUPON_H

#include <string>
#include "Date.h"

class Coupon {
public:
    Coupon();
    Coupon(int id, const std::string& code, const std::string& discountType,
           double discountValue, double minAmount, const Date& expiryDate,
           int maxUsage, int currentUsage, bool active);

    int getId() const;
    std::string getCode() const;
    std::string getDiscountType() const;
    double getDiscountValue() const;
    double getMinAmount() const;
    Date getExpiryDate() const;
    int getMaxUsage() const;
    int getCurrentUsage() const;
    bool isActive() const;

    void setActive(bool active);
    void incrementUsage();
    bool isValidFor(double amount, const Date& today) const;
    double calculateDiscount(double amount) const;

private:
    int id;
    std::string code;
    std::string discountType;
    double discountValue;
    double minAmount;
    Date expiryDate;
    int maxUsage;
    int currentUsage;
    bool active;
};

#endif
