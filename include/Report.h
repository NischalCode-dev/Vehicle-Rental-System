#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "Booking.h"
#include "User.h"
#include "Vehicle.h"

class Report {
public:
    Report();
    Report(const std::vector<Vehicle>& vehicles, const std::vector<User>& users, const std::vector<Booking>& bookings);

    void showVehicleSummary() const;
    void showCustomerSummary() const;
    void showFinancialSummary() const;
    void showDashboardSummary() const;
    void showRevenueAnalytics() const;
    void showPopularVehicles() const;

private:
    std::vector<Vehicle> vehicles;
    std::vector<User> users;
    std::vector<Booking> bookings;
};

#endif
