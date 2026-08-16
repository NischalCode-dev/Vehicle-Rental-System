// #include "Invoice.h"

// #include <iostream>
// #include <sstream>
// #include <string>

// #include "Utils.h"

// Invoice::Invoice() {}

// Invoice::Invoice(const Booking& booking, const Vehicle& vehicle, const User& customer, const Payment& payment)
//     : booking(booking), vehicle(vehicle), customer(customer), payment(payment) {}

// std::string Invoice::buildText() const {
//     std::ostringstream oss;
//     oss << "# ========================================\n";
//     oss << "VEHICLE RENTAL INVOICE\n";
//     oss << "Booking ID : BK" << booking.getId() << "\n";
//     oss << "Customer : " << customer.getName() << "\n";
//     oss << "Vehicle : " << vehicle.getBrand() << " " << vehicle.getModel() << "\n";
//     oss << "Vehicle Number : " << vehicle.getVehicleNumber() << "\n";
//     oss << "Pickup Date : " << booking.getPickupDate().toString() << "\n";
//     oss << "Return Date : " << booking.getReturnDate().toString() << "\n";
//     oss << "Rental Days : " << booking.getRentalDays() << "\n";
//     oss << "Price Per Day : Rs. " << utils::formatMoney(vehicle.getPricePerDay()) << "\n";
//     oss << "Rental Cost : Rs. " << utils::formatMoney(booking.getRentalPrice()) << "\n";
//     oss << "Payment Method : " << payment.getMethod() << "\n";
//     oss << "Payment Status : " << payment.getStatus() << "\n";
//     oss << "Transaction ID : " << payment.getTransactionId() << "\n";
//     oss << "========================================\n";
//     return oss.str();
// }

// void Invoice::display() const {
//     std::cout << buildText();
// }
#include "Invoice.h"

#include <iostream>
#include <sstream>
#include "Utils.h"

Invoice::Invoice() {}

Invoice::Invoice(const Booking& booking,
                 const Vehicle& vehicle,
                 const User& customer,
                 const Payment& payment)
    : booking(booking),
      vehicle(vehicle),
      customer(customer),
      payment(payment) {
}

std::string Invoice::buildText() const {
    std::ostringstream oss;

    // double rentalCost = booking.getRentalPrice();
    // double lateFee = booking.getLateFee();
    // double fuelCharge = booking.getFuelCharge();
    // double damageCharge = booking.getDamageCharge();

    // double totalAmount =
    //     rentalCost +
    //     lateFee +
    //     fuelCharge +
    //     damageCharge;
    double finalRentalCost =
    booking.getRentalPrice();

double discount =
    booking.getDiscountAmount();

double baseRentalCost =
    finalRentalCost + discount;

double lateFee =
    booking.getLateFee();

double fuelCharge =
    booking.getFuelCharge();

double damageCharge =
    booking.getDamageCharge();

double totalAmount =
    finalRentalCost +
    lateFee +
    fuelCharge +
    damageCharge;

    oss << "\n";
    oss << "============================================================\n";
    oss << "                 VEHICLE RENTAL INVOICE\n";
    oss << "============================================================\n";

    oss << "Invoice Reference : INV-BK" << booking.getId() << "\n";
    oss << "Booking ID        : BK" << booking.getId() << "\n";
    oss << "Transaction ID    : " << payment.getTransactionId() << "\n";

    oss << "------------------------------------------------------------\n";
    oss << "CUSTOMER DETAILS\n";
    oss << "------------------------------------------------------------\n";

    oss << "Customer ID       : " << customer.getId() << "\n";
    oss << "Customer Name     : " << customer.getName() << "\n";
    oss << "Email             : " << customer.getEmail() << "\n";
    oss << "Phone             : " << customer.getPhone() << "\n";

    oss << "------------------------------------------------------------\n";
    oss << "VEHICLE DETAILS\n";
    oss << "------------------------------------------------------------\n";

    oss << "Vehicle ID        : " << vehicle.getId() << "\n";
    oss << "Vehicle           : "
        << vehicle.getBrand() << " "
        << vehicle.getModel() << "\n";

    oss << "Vehicle Number    : "
        << vehicle.getVehicleNumber() << "\n";

    oss << "Vehicle Type      : "
        << vehicle.getType() << "\n";

    oss << "------------------------------------------------------------\n";
    oss << "RENTAL DETAILS\n";
    oss << "------------------------------------------------------------\n";

    oss << "Pickup Date       : "
        << booking.getPickupDate().toString() << "\n";

    oss << "Return Date       : "
        << booking.getReturnDate().toString() << "\n";

    oss << "Rental Days       : "
        << booking.getRentalDays() << "\n";

    oss << "Price Per Day     : Rs. "
        << utils::formatMoney(vehicle.getPricePerDay()) << "\n";

    oss << "------------------------------------------------------------\n";
    oss << "CHARGES\n";
    oss << "------------------------------------------------------------\n";

   oss << "Base Rental       : Rs. "
    << utils::formatMoney(baseRentalCost)
    << "\n";

if (!booking.getCouponCode().empty()) {

    oss << "Coupon            : "
        << booking.getCouponCode()
        << "\n";

    oss << "Discount          : -Rs. "
        << utils::formatMoney(discount)
        << "\n";

    oss << "Rental After Disc.: Rs. "
        << utils::formatMoney(finalRentalCost)
        << "\n";
}

    oss << "Late Fee          : Rs. "
        << utils::formatMoney(lateFee) << "\n";

    oss << "Fuel Charge       : Rs. "
        << utils::formatMoney(fuelCharge) << "\n";

    oss << "Damage Charge     : Rs. "
        << utils::formatMoney(damageCharge) << "\n";

    oss << "------------------------------------------------------------\n";

    oss << "TOTAL AMOUNT      : Rs. "
        << utils::formatMoney(totalAmount) << "\n";

    oss << "------------------------------------------------------------\n";
    oss << "PAYMENT DETAILS\n";
    oss << "------------------------------------------------------------\n";

    oss << "Payment Method    : "
        << payment.getMethod() << "\n";

    oss << "Payment Status    : "
        << payment.getStatus() << "\n";

    oss << "Payment Date      : "
        << payment.getPaymentDate() << "\n";

    oss << "Transaction ID    : "
        << payment.getTransactionId() << "\n";

    oss << "============================================================\n";
    oss << "              THANK YOU FOR RENTING WITH US!\n";
    oss << "============================================================\n";

    return oss.str();
}

void Invoice::display() const {
    std::cout << buildText();
}