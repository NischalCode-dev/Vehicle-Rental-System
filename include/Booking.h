// #ifndef BOOKING_H
// #define BOOKING_H

// #include <string>
// #include "Date.h"

// class Booking {
// public:
//     Booking();
//     Booking(int id, int customerId, int vehicleId, const Date& pickupDate,
//             const Date& returnDate, const std::string& pickupLocation,
//             const std::string& returnLocation, int rentalDays, double rentalPrice,
//             const std::string& status, const Date& createdDate);

//     int getId() const;
//     int getCustomerId() const;
//     int getVehicleId() const;
//     Date getPickupDate() const;
//     Date getReturnDate() const;
//     std::string getPickupLocation() const;
//     std::string getReturnLocation() const;
//     int getRentalDays() const;
//     double getRentalPrice() const;
//     std::string getStatus() const;
//     Date getCreatedDate() const;
//     std::string getPickupCondition() const;
//     int getOdometerAtPickup() const;
//     int getFuelAtPickup() const;
//     std::string getReturnCondition() const;
//     int getOdometerAtReturn() const;
//     int getFuelAtReturn() const;
//     std::string getDamageInfo() const;
//     int getLateDays() const;
//     double getLateFee() const;
//     double getFuelCharge() const;
//     double getDamageCharge() const;

//     void setStatus(const std::string& status);
//     void setPickupCondition(const std::string& condition);
//     void setOdometerAtPickup(int value);
//     void setFuelAtPickup(int value);
//     void setReturnCondition(const std::string& condition);
//     void setOdometerAtReturn(int value);
//     void setFuelAtReturn(int value);
//     void setDamageInfo(const std::string& info);
//     void setLateDays(int value);
//     void setLateFee(double value);
//     void setFuelCharge(double value);
//     void setDamageCharge(double value);

// private:
//     int id;
//     int customerId;
//     int vehicleId;
//     Date pickupDate;
//     Date returnDate;
//     std::string pickupLocation;
//     std::string returnLocation;
//     int rentalDays;
//     double rentalPrice;
//     std::string status;
//     Date createdDate;
//     std::string pickupCondition;
//     int odometerAtPickup;
//     int fuelAtPickup;
//     std::string returnCondition;
//     int odometerAtReturn;
//     int fuelAtReturn;
//     std::string damageInfo;
//     int lateDays;
//     double lateFee;
//     double fuelCharge;
//     double damageCharge;
// };

// #endif
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "Date.h"

class Booking {
public:
    Booking();

    Booking(int id, int customerId, int vehicleId,
            const Date& pickupDate,
            const Date& returnDate,
            const std::string& pickupLocation,
            const std::string& returnLocation,
            int rentalDays,
            double rentalPrice,
            const std::string& status,
            const Date& createdDate,
            const std::string& couponCode = "",
            double discountAmount = 0.0);

    int getId() const;
    int getCustomerId() const;
    int getVehicleId() const;
    Date getPickupDate() const;
    Date getReturnDate() const;
    std::string getPickupLocation() const;
    std::string getReturnLocation() const;
    int getRentalDays() const;
    double getRentalPrice() const;
    std::string getStatus() const;
    Date getCreatedDate() const;

    std::string getCouponCode() const;
    double getDiscountAmount() const;

    std::string getPickupCondition() const;
    int getOdometerAtPickup() const;
    int getFuelAtPickup() const;
    std::string getReturnCondition() const;
    int getOdometerAtReturn() const;
    int getFuelAtReturn() const;
    std::string getDamageInfo() const;
    int getLateDays() const;
    double getLateFee() const;
    double getFuelCharge() const;
    double getDamageCharge() const;

    void setStatus(const std::string& status);
    void setPickupCondition(const std::string& condition);
    void setOdometerAtPickup(int value);
    void setFuelAtPickup(int value);
    void setReturnCondition(const std::string& condition);
    void setOdometerAtReturn(int value);
    void setFuelAtReturn(int value);
    void setDamageInfo(const std::string& info);
    void setLateDays(int value);
    void setLateFee(double value);
    void setFuelCharge(double value);
    void setDamageCharge(double value);

private:
    int id;
    int customerId;
    int vehicleId;

    Date pickupDate;
    Date returnDate;

    std::string pickupLocation;
    std::string returnLocation;

    int rentalDays;

    // This stores the FINAL rental price after coupon discount.
    double rentalPrice;

    std::string status;
    Date createdDate;

    // Coupon information
    std::string couponCode;
    double discountAmount;

    std::string pickupCondition;
    int odometerAtPickup;
    int fuelAtPickup;

    std::string returnCondition;
    int odometerAtReturn;
    int fuelAtReturn;

    std::string damageInfo;

    int lateDays;
    double lateFee;
    double fuelCharge;
    double damageCharge;
};

#endif