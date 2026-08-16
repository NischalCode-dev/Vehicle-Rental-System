// #include "Booking.h"

// Booking::Booking() : id(0), customerId(0), vehicleId(0), pickupDate(), returnDate(), pickupLocation(""), returnLocation(""), rentalDays(0), rentalPrice(0.0), status("BOOKED"), createdDate(), pickupCondition(""), odometerAtPickup(0), fuelAtPickup(0), returnCondition(""), odometerAtReturn(0), fuelAtReturn(0), damageInfo(""), lateDays(0), lateFee(0.0), fuelCharge(0.0), damageCharge(0.0) {}

// Booking::Booking(int id, int customerId, int vehicleId, const Date& pickupDate,
//                  const Date& returnDate, const std::string& pickupLocation,
//                  const std::string& returnLocation, int rentalDays, double rentalPrice,
//                  const std::string& status, const Date& createdDate)
//     : id(id), customerId(customerId), vehicleId(vehicleId), pickupDate(pickupDate), returnDate(returnDate), pickupLocation(pickupLocation), returnLocation(returnLocation), rentalDays(rentalDays), rentalPrice(rentalPrice), status(status), createdDate(createdDate), pickupCondition(""), odometerAtPickup(0), fuelAtPickup(0), returnCondition(""), odometerAtReturn(0), fuelAtReturn(0), damageInfo(""), lateDays(0), lateFee(0.0), fuelCharge(0.0), damageCharge(0.0) {}

// int Booking::getId() const { return id; }
// int Booking::getCustomerId() const { return customerId; }
// int Booking::getVehicleId() const { return vehicleId; }
// Date Booking::getPickupDate() const { return pickupDate; }
// Date Booking::getReturnDate() const { return returnDate; }
// std::string Booking::getPickupLocation() const { return pickupLocation; }
// std::string Booking::getReturnLocation() const { return returnLocation; }
// int Booking::getRentalDays() const { return rentalDays; }
// double Booking::getRentalPrice() const { return rentalPrice; }
// std::string Booking::getStatus() const { return status; }
// Date Booking::getCreatedDate() const { return createdDate; }
// std::string Booking::getPickupCondition() const { return pickupCondition; }
// int Booking::getOdometerAtPickup() const { return odometerAtPickup; }
// int Booking::getFuelAtPickup() const { return fuelAtPickup; }
// std::string Booking::getReturnCondition() const { return returnCondition; }
// int Booking::getOdometerAtReturn() const { return odometerAtReturn; }
// int Booking::getFuelAtReturn() const { return fuelAtReturn; }
// std::string Booking::getDamageInfo() const { return damageInfo; }
// int Booking::getLateDays() const { return lateDays; }
// double Booking::getLateFee() const { return lateFee; }
// double Booking::getFuelCharge() const { return fuelCharge; }
// double Booking::getDamageCharge() const { return damageCharge; }

// void Booking::setStatus(const std::string& value) { status = value; }
// void Booking::setPickupCondition(const std::string& value) { pickupCondition = value; }
// void Booking::setOdometerAtPickup(int value) { odometerAtPickup = value; }
// void Booking::setFuelAtPickup(int value) { fuelAtPickup = value; }
// void Booking::setReturnCondition(const std::string& value) { returnCondition = value; }
// void Booking::setOdometerAtReturn(int value) { odometerAtReturn = value; }
// void Booking::setFuelAtReturn(int value) { fuelAtReturn = value; }
// void Booking::setDamageInfo(const std::string& value) { damageInfo = value; }
// void Booking::setLateDays(int value) { lateDays = value; }
// void Booking::setLateFee(double value) { lateFee = value; }
// void Booking::setFuelCharge(double value) { fuelCharge = value; }
// void Booking::setDamageCharge(double value) { damageCharge = value; }
#include "Booking.h"

Booking::Booking()
    : id(0),
      customerId(0),
      vehicleId(0),
      pickupDate(),
      returnDate(),
      pickupLocation(""),
      returnLocation(""),
      rentalDays(0),
      rentalPrice(0.0),
      status("BOOKED"),
      createdDate(),
      couponCode(""),
      discountAmount(0.0),
      pickupCondition(""),
      odometerAtPickup(0),
      fuelAtPickup(0),
      returnCondition(""),
      odometerAtReturn(0),
      fuelAtReturn(0),
      damageInfo(""),
      lateDays(0),
      lateFee(0.0),
      fuelCharge(0.0),
      damageCharge(0.0) {
}

Booking::Booking(
    int id,
    int customerId,
    int vehicleId,
    const Date& pickupDate,
    const Date& returnDate,
    const std::string& pickupLocation,
    const std::string& returnLocation,
    int rentalDays,
    double rentalPrice,
    const std::string& status,
    const Date& createdDate,
    const std::string& couponCode,
    double discountAmount
)
    : id(id),
      customerId(customerId),
      vehicleId(vehicleId),
      pickupDate(pickupDate),
      returnDate(returnDate),
      pickupLocation(pickupLocation),
      returnLocation(returnLocation),
      rentalDays(rentalDays),
      rentalPrice(rentalPrice),
      status(status),
      createdDate(createdDate),
      couponCode(couponCode),
      discountAmount(discountAmount),
      pickupCondition(""),
      odometerAtPickup(0),
      fuelAtPickup(0),
      returnCondition(""),
      odometerAtReturn(0),
      fuelAtReturn(0),
      damageInfo(""),
      lateDays(0),
      lateFee(0.0),
      fuelCharge(0.0),
      damageCharge(0.0) {
}

int Booking::getId() const { return id; }
int Booking::getCustomerId() const { return customerId; }
int Booking::getVehicleId() const { return vehicleId; }

Date Booking::getPickupDate() const {
    return pickupDate;
}

Date Booking::getReturnDate() const {
    return returnDate;
}

std::string Booking::getPickupLocation() const {
    return pickupLocation;
}

std::string Booking::getReturnLocation() const {
    return returnLocation;
}

int Booking::getRentalDays() const {
    return rentalDays;
}

double Booking::getRentalPrice() const {
    return rentalPrice;
}

std::string Booking::getStatus() const {
    return status;
}

Date Booking::getCreatedDate() const {
    return createdDate;
}

std::string Booking::getCouponCode() const {
    return couponCode;
}

double Booking::getDiscountAmount() const {
    return discountAmount;
}

std::string Booking::getPickupCondition() const {
    return pickupCondition;
}

int Booking::getOdometerAtPickup() const {
    return odometerAtPickup;
}

int Booking::getFuelAtPickup() const {
    return fuelAtPickup;
}

std::string Booking::getReturnCondition() const {
    return returnCondition;
}

int Booking::getOdometerAtReturn() const {
    return odometerAtReturn;
}

int Booking::getFuelAtReturn() const {
    return fuelAtReturn;
}

std::string Booking::getDamageInfo() const {
    return damageInfo;
}

int Booking::getLateDays() const {
    return lateDays;
}

double Booking::getLateFee() const {
    return lateFee;
}

double Booking::getFuelCharge() const {
    return fuelCharge;
}

double Booking::getDamageCharge() const {
    return damageCharge;
}

void Booking::setStatus(const std::string& value) {
    status = value;
}

void Booking::setPickupCondition(const std::string& value) {
    pickupCondition = value;
}

void Booking::setOdometerAtPickup(int value) {
    odometerAtPickup = value;
}

void Booking::setFuelAtPickup(int value) {
    fuelAtPickup = value;
}

void Booking::setReturnCondition(const std::string& value) {
    returnCondition = value;
}

void Booking::setOdometerAtReturn(int value) {
    odometerAtReturn = value;
}

void Booking::setFuelAtReturn(int value) {
    fuelAtReturn = value;
}

void Booking::setDamageInfo(const std::string& value) {
    damageInfo = value;
}

void Booking::setLateDays(int value) {
    lateDays = value;
}

void Booking::setLateFee(double value) {
    lateFee = value;
}

void Booking::setFuelCharge(double value) {
    fuelCharge = value;
}

void Booking::setDamageCharge(double value) {
    damageCharge = value;
}