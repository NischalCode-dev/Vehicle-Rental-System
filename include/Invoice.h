#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include <vector>
#include "Booking.h"
#include "Payment.h"
#include "Vehicle.h"
#include "User.h"

class Invoice {
public:
    Invoice();
    Invoice(const Booking& booking, const Vehicle& vehicle, const User& customer, const Payment& payment);

    void display() const;
    std::string buildText() const;

private:
    Booking booking;
    Vehicle vehicle;
    User customer;
    Payment payment;
};

#endif
