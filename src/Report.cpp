#include "Report.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "Date.h"
#include "Utils.h"

namespace {
    Date currentDate() {
        std::time_t now = std::time(nullptr);
        std::tm* local = std::localtime(&now);
        return Date(local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
    }

    bool isBookingActive(const Booking& booking) {
        const std::string status = booking.getStatus();
        return status == "BOOKED" || status == "PENDING" || status == "CONFIRMED" || status == "PICKED_UP";
    }

    bool isBookingCompleted(const Booking& booking) {
        return booking.getStatus() == "COMPLETED";
    }

    double bookingRevenue(const Booking& booking) {
        return booking.getRentalPrice() + booking.getLateFee() + booking.getFuelCharge() + booking.getDamageCharge();
    }

    std::string statusLabel(const std::string& status) {
        if (status == "AVAILABLE") return "AVAILABLE";
        if (status == "BOOKED") return "BOOKED";
        if (status == "RENTED") return "RENTED";
        if (status == "MAINTENANCE") return "MAINTENANCE";
        return "INACTIVE";
    }
}

Report::Report() {}

Report::Report(const std::vector<Vehicle>& vehicles, const std::vector<User>& users, const std::vector<Booking>& bookings)
    : vehicles(vehicles), users(users), bookings(bookings) {}

void Report::showVehicleSummary() const {
    utils::printHeader("VEHICLE REPORT");
    std::cout << "Total vehicles: " << vehicles.size() << "\n";
    int available = 0;
    int booked = 0;
    int rented = 0;
    int maintenance = 0;
    int inactive = 0;
    for (const auto& vehicle : vehicles) {
        const std::string status = vehicle.getStatus();
        if (status == "AVAILABLE") {
            ++available;
        } else if (status == "BOOKED") {
            ++booked;
        } else if (status == "RENTED") {
            ++rented;
        } else if (status == "MAINTENANCE") {
            ++maintenance;
        } else {
            ++inactive;
        }
    }
    std::cout << "Available vehicles: " << available << "\n";
    std::cout << "Booked vehicles: " << booked << "\n";
    std::cout << "Rented vehicles: " << rented << "\n";
    std::cout << "Maintenance vehicles: " << maintenance << "\n";
    std::cout << "Inactive vehicles: " << inactive << "\n";
}

void Report::showCustomerSummary() const {
    utils::printHeader("CUSTOMER REPORT");
    std::cout << "Total customers: " << users.size() << "\n";
}

void Report::showFinancialSummary() const {
    utils::printHeader("FINANCIAL REPORT");
    double total = 0.0;
    for (const auto& booking : bookings) {
        total += bookingRevenue(booking);
    }
    std::cout << "Total revenue: Rs. " << utils::formatMoney(total) << "\n";
}

void Report::showDashboardSummary() const {
    utils::printHeader("ADMIN DASHBOARD");
    std::cout << "🚗 Total Vehicles : " << vehicles.size() << "\n";
    int available = 0;
    int booked = 0;
    int rented = 0;
    int maintenance = 0;
    int inactive = 0;
    for (const auto& vehicle : vehicles) {
        const std::string status = vehicle.getStatus();
        if (status == "AVAILABLE") ++available;
        else if (status == "BOOKED") ++booked;
        else if (status == "RENTED") ++rented;
        else if (status == "MAINTENANCE") ++maintenance;
        else ++inactive;
    }
    std::cout << "🟢 Available : " << available << "\n";
    std::cout << "🔵 Booked : " << booked << "\n";
    std::cout << "🔴 Rented : " << rented << "\n";
    std::cout << "🟡 Maintenance : " << maintenance << "\n";
    std::cout << "⚫ Inactive : " << inactive << "\n";

    std::cout << "\n👥 Customers : " << users.size() << "\n";
    int active = 0;
    int completed = 0;
    int cancelled = 0;
    for (const auto& booking : bookings) {
        const std::string status = booking.getStatus();
        if (isBookingActive(booking)) ++active;
        if (isBookingCompleted(booking)) ++completed;
        if (status == "CANCELLED") ++cancelled;
    }
    std::cout << "📅 Active Bookings : " << active << "\n";
    std::cout << "✅ Completed Bookings : " << completed << "\n";
    std::cout << "❌ Cancelled Bookings : " << cancelled << "\n";

    double totalRevenue = 0.0;
    double todayRevenue = 0.0;
    double weeklyRevenue = 0.0;
    double monthlyRevenue = 0.0;
    double yearlyRevenue = 0.0;
    const Date today = currentDate();
    for (const auto& booking : bookings) {
        const double revenue = bookingRevenue(booking);
        totalRevenue += revenue;
        if (booking.getCreatedDate() == today) {
            todayRevenue += revenue;
        }
        const int daysBetween = Date::daysBetween(booking.getCreatedDate(), today);
        if (daysBetween >= 0 && daysBetween <= 7) {
            weeklyRevenue += revenue;
        }
        if (booking.getCreatedDate().year() == today.year() && booking.getCreatedDate().month() == today.month()) {
            monthlyRevenue += revenue;
        }
        if (booking.getCreatedDate().year() == today.year()) {
            yearlyRevenue += revenue;
        }
    }

    std::cout << "\n💰 Total Revenue : Rs. " << utils::formatMoney(totalRevenue) << "\n";
    std::cout << "📆 Today's Revenue : Rs. " << utils::formatMoney(todayRevenue) << "\n";
    std::cout << "📈 Weekly Revenue : Rs. " << utils::formatMoney(weeklyRevenue) << "\n";
    std::cout << "🗓️ Monthly Revenue : Rs. " << utils::formatMoney(monthlyRevenue) << "\n";
    std::cout << "📅 Yearly Revenue : Rs. " << utils::formatMoney(yearlyRevenue) << "\n";
}

void Report::showRevenueAnalytics() const {
    utils::printHeader("REVENUE ANALYTICS");
    std::map<std::string, double> typeRevenue;
    std::map<std::string, double> vehicleRevenue;
    double lateFees = 0.0;
    double damageCharges = 0.0;
    double fuelCharges = 0.0;

    for (const auto& booking : bookings) {
        lateFees += booking.getLateFee();
        damageCharges += booking.getDamageCharge();
        fuelCharges += booking.getFuelCharge();

        const auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
            return vehicle.getId() == booking.getVehicleId();
        });
        if (vehicleIt != vehicles.end()) {
            const std::string type = vehicleIt->getType();
            typeRevenue[type] += bookingRevenue(booking);
            vehicleRevenue[vehicleIt->getBrand() + " " + vehicleIt->getModel()] += bookingRevenue(booking);
        }
    }

    std::cout << "Revenue by vehicle type:\n";
    double maxTypeRevenue = 0.0;
    for (const auto& entry : typeRevenue) {
        maxTypeRevenue = std::max(maxTypeRevenue, entry.second);
    }
    for (const auto& entry : typeRevenue) {
        const int barLength = maxTypeRevenue > 0 ? static_cast<int>(20 * entry.second / maxTypeRevenue) : 0;
        std::cout << entry.first << " " << std::string(barLength, '#') << " Rs. " << utils::formatMoney(entry.second) << "\n";
    }

    std::cout << "\nRevenue by vehicle:\n";
    double maxVehicleRevenue = 0.0;
    for (const auto& entry : vehicleRevenue) {
        maxVehicleRevenue = std::max(maxVehicleRevenue, entry.second);
    }
    for (const auto& entry : vehicleRevenue) {
        const int barLength = maxVehicleRevenue > 0 ? static_cast<int>(20 * entry.second / maxVehicleRevenue) : 0;
        std::cout << entry.first << " " << std::string(barLength, '#') << " Rs. " << utils::formatMoney(entry.second) << "\n";
    }

    std::cout << "\nLate fees: Rs. " << utils::formatMoney(lateFees) << "\n";
    std::cout << "Damage charges: Rs. " << utils::formatMoney(damageCharges) << "\n";
    std::cout << "Fuel charges: Rs. " << utils::formatMoney(fuelCharges) << "\n";
}

void Report::showPopularVehicles() const {
    utils::printHeader("MOST POPULAR VEHICLES");
    std::map<int, int> bookingCounts;
    std::map<int, double> revenueByVehicle;

    for (const auto& booking : bookings) {
        if (booking.getStatus() == "CANCELLED") {
            continue;
        }
        ++bookingCounts[booking.getVehicleId()];
        revenueByVehicle[booking.getVehicleId()] += bookingRevenue(booking);
    }

    std::vector<std::pair<int, int>> ranked;
    for (const auto& entry : bookingCounts) {
        ranked.push_back({entry.first, entry.second});
    }
    std::sort(ranked.begin(), ranked.end(), [](const auto& left, const auto& right) {
        return left.second > right.second;
    });

    std::cout << "Top vehicles by booking history:\n";
    int position = 1;
    for (const auto& entry : ranked) {
        const auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
            return vehicle.getId() == entry.first;
        });
        if (vehicleIt != vehicles.end()) {
            const std::string medal = position == 1 ? "🥇" : position == 2 ? "🥈" : position == 3 ? "🥉" : std::to_string(position) + ".";
            std::cout << medal << " " << vehicleIt->getBrand() << " " << vehicleIt->getModel()
                      << " - " << entry.second << " bookings"
                      << " | Revenue: Rs. " << utils::formatMoney(revenueByVehicle[entry.first]) << "\n";
            ++position;
        }
    }

    if (ranked.empty()) {
        std::cout << "No booking history available yet.\n";
    }

    std::cout << "\nMost popular vehicle type:\n";
    std::map<std::string, int> typeCounts;
    for (const auto& booking : bookings) {
        if (booking.getStatus() == "CANCELLED") {
            continue;
        }
        const auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
            return vehicle.getId() == booking.getVehicleId();
        });
        if (vehicleIt != vehicles.end()) {
            ++typeCounts[vehicleIt->getType()];
        }
    }
    std::pair<std::string, int> topType("Unknown", 0);
    for (const auto& entry : typeCounts) {
        if (entry.second > topType.second) {
            topType = entry;
        }
    }
    std::cout << topType.first << " - " << topType.second << " bookings\n";
}
