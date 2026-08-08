#include "Invoice.h"

#include <iostream>
#include <sstream>
#include <string>

#include "Utils.h"

Invoice::Invoice() {}

Invoice::Invoice(const Booking& booking, const Vehicle& vehicle, const User& customer, const Payment& payment)
    : booking(booking), vehicle(vehicle), customer(customer), payment(payment) {}

std::string Invoice::buildText() const {
    std::ostringstream oss;
    oss << "# ========================================\n";
    oss << "VEHICLE RENTAL INVOICE\n";
    oss << "Booking ID : BK" << booking.getId() << "\n";
    oss << "Customer : " << customer.getName() << "\n";
    oss << "Vehicle : " << vehicle.getBrand() << " " << vehicle.getModel() << "\n";
    oss << "Vehicle Number : " << vehicle.getVehicleNumber() << "\n";
    oss << "Pickup Date : " << booking.getPickupDate().toString() << "\n";
    oss << "Return Date : " << booking.getReturnDate().toString() << "\n";
    oss << "Rental Days : " << booking.getRentalDays() << "\n";
    oss << "Price Per Day : Rs. " << utils::formatMoney(vehicle.getPricePerDay()) << "\n";
    oss << "Rental Cost : Rs. " << utils::formatMoney(booking.getRentalPrice()) << "\n";
    oss << "Payment Method : " << payment.getMethod() << "\n";
    oss << "Payment Status : " << payment.getStatus() << "\n";
    oss << "Transaction ID : " << payment.getTransactionId() << "\n";
    oss << "========================================\n";
    return oss.str();
}

void Invoice::display() const {
    std::cout << buildText();
}
