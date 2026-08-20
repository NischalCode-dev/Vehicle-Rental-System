#include "RentalSystem.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "FileManager.h"
#include "Utils.h"

namespace
{
    const std::string kUsersPath = "data/users.txt";
    const std::string kVehiclesPath = "data/vehicles.txt";
    const std::string kBookingsPath = "data/bookings.txt";
    const std::string kPaymentsPath = "data/payments.txt";
    const std::string kMaintenancePath = "data/maintenance.txt";
    const std::string kReviewsPath = "data/reviews.txt";
    const std::string kCouponsPath = "data/coupons.txt";
    const std::string kNotificationsPath = "data/notifications.txt";
    const std::string kFavoritesPath = "data/favorites.txt";

    std::string currentDateString()
    {
        std::time_t now = std::time(nullptr);
        std::tm *local = std::localtime(&now);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", local);
        return std::string(buffer);
    }
}

RentalSystem::RentalSystem() : currentUser(nullptr), loggedIn(false), nextUserId(1), nextVehicleId(1), nextBookingId(1), nextPaymentId(1), nextMaintenanceId(1), nextReviewId(1)
{
    initializeDataFiles();
    loadUsers();
    loadVehicles();
    loadBookings();
    loadPayments();
    loadMaintenance();
    loadReviews();
}

void RentalSystem::run()
{
    while (true)
    {
        utils::clearScreen();
        utils::printHeader("\nVEHICLE RENTAL SYSTEM");
        utils::printBox("WELCOME", {"\nOffline vehicle rental management system",
                                    "Register a customer account or browse vehicles",
                                    "All data is stored locally in text files"});
        utils::printDivider(60);
        std::cout << "[1] Login\n";
        std::cout << "[2] Register Customer\n";
        std::cout << "[3] Browse Vehicles\n";
        std::cout << "[4] About Project\n";
        std::cout << "[5] Exit\n";
        int choice = utils::getInt("Enter choice: ");

        switch (choice)
        {
        case 1:
            loginUser();
            break;
        case 2:
            registerCustomer();
            break;
        case 3:
            browseVehicles();
            break;
        case 4:
            displayAbout();
            break;
        case 5:
            utils::printSuccess("Exiting the application. Goodbye!");
            return;
        default:
            utils::printError("Invalid choice.");
        }
        if (choice != 5)
        {
            utils::pauseScreen();
        }
    }
}

void RentalSystem::initializeDataFiles()
{
    FileManager::ensureFile(kUsersPath);
    FileManager::ensureFile(kVehiclesPath);
    FileManager::ensureFile(kBookingsPath);
    FileManager::ensureFile(kPaymentsPath);
    FileManager::ensureFile(kMaintenancePath);
    FileManager::ensureFile(kReviewsPath);
    FileManager::ensureFile(kCouponsPath);
    FileManager::ensureFile(kNotificationsPath);
    FileManager::ensureFile(kFavoritesPath);
    seedSampleData();
    loadCoupons();
    loadNotifications();
    loadFavorites();
}

void RentalSystem::showMainMenu()
{
    std::cout << "Main Menu placeholder.\n";
}

void RentalSystem::showAdminMenu()
{
    std::cout << "Admin menu placeholder.\n";
}

void RentalSystem::showCustomerMenu()
{
    std::cout << "Customer menu placeholder.\n";
}

void RentalSystem::displayAbout()
{
    utils::clearScreen();
    utils::printHeader("ABOUT THIS PROJECT");
    utils::printBox("PROJECT OVERVIEW", {"Modular C++ console-based rental system",
                                         "Features include authentication, vehicles, bookings,",
                                         "payments, maintenance, reviews, and reports",
                                         "Data is stored locally using text files"});
    utils::printInfo("This version is designed for learning, offline use, and simple console based applications. It can be further extended for product level application with GUI and database support.");
}

void RentalSystem::seedSampleData()
{
    if (!vehicles.empty())
    {
        return;
    }

    vehicles.emplace_back(nextVehicleId++, "BA 12 PA 1234", "Toyota", "Corolla", "Car", 2022, "White", "Petrol", "Automatic", 5, 3000.0, 18000.0, "AVAILABLE");
    vehicles.emplace_back(nextVehicleId++, "BA 14 HA 5678", "Hyundai", "Creta", "SUV", 2021, "Black", "Diesel", "Manual", 5, 4000.0, 22000.0, "AVAILABLE");
    vehicles.emplace_back(nextVehicleId++, "BA 16 CA 9012", "Honda", "Civic", "Car", 2020, "Silver", "Petrol", "Automatic", 5, 3500.0, 15000.0, "BOOKED");
    vehicles.emplace_back(nextVehicleId++, "BA 18 RA 3456", "Yamaha", "R15", "Bike", 2023, "Blue", "Petrol", "Manual", 2, 1200.0, 9000.0, "AVAILABLE");
    saveVehicles();
}

void RentalSystem::registerCustomer()
{
    std::string name = utils::getNonEmptyString("Full name: ");
    std::string email = utils::getNonEmptyString("Email: ");
    std::string phone = utils::getNonEmptyString("Phone: ");
    std::string username = utils::getNonEmptyString("Username: ");
    std::string password = utils::getNonEmptyString("Password: ");

    if (!utils::isValidEmail(email))
    {
        std::cout << "[ERROR] Invalid email format.\n";
        return;
    }
    if (!utils::isValidPhone(phone))
    {
        std::cout << "[ERROR] Invalid phone number.\n";
        return;
    }
    if (isUsernameTaken(username))
    {
        std::cout << "[ERROR] Username already exists.\n";
        return;
    }

    users.emplace_back(nextUserId++, name, email, phone, username, password, "customer");
    saveUsers();
    std::cout << "[SUCCESS] Customer registered successfully.\n";
}

void RentalSystem::loginUser()
{
    std::string username = utils::getNonEmptyString("Username: ");
    std::string password = utils::getNonEmptyString("Password: ");

    std::string role;
    if (authenticate(username, password, role))
    {
        loggedIn = true;
        currentUser = nullptr;
        if (role != "admin")
        {
            auto it = std::find_if(users.begin(), users.end(), [&](const User &user)
                                   { return user.getUsername() == username; });
            if (it != users.end())
            {
                currentUser = &(*it);
            }
        }
        std::cout << "[SUCCESS] Login successful.\n";
        if (role == "admin")
        {
            showAdminDashboard();
        }
        else
        {
            showCustomerDashboard();
        }
    }
    else
    {
        std::cout << "[ERROR] Invalid username or password.\n";
    }
}

void RentalSystem::loadUsers()
{
    users.clear();
    auto lines = FileManager::readLines(kUsersPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 7)
        {
            try
            {
                int id = std::stoi(parts[0]);
                users.emplace_back(id, parts[1], parts[2], parts[3], parts[4], parts[5], parts[6]);
                if (id >= nextUserId)
                {
                    nextUserId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}

void RentalSystem::saveUsers()
{
    std::vector<std::string> lines;
    for (const auto &user : users)
    {
        lines.push_back(FileManager::join({std::to_string(user.getId()), user.getName(), user.getEmail(), user.getPhone(), user.getUsername(), user.getPassword(), user.getRole()}, '|'));
    }
    FileManager::writeLines(kUsersPath, lines);
}

void RentalSystem::loadVehicles()
{
    vehicles.clear();
    auto lines = FileManager::readLines(kVehiclesPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 13)
        {
            try
            {
                int id = std::stoi(parts[0]);
                vehicles.emplace_back(id, parts[1], parts[2], parts[3], parts[4], std::stoi(parts[5]), parts[6], parts[7], parts[8], std::stoi(parts[9]), std::stod(parts[10]), std::stod(parts[11]), parts[12]);
                if (id >= nextVehicleId)
                {
                    nextVehicleId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}

void RentalSystem::saveVehicles()
{
    std::vector<std::string> lines;
    for (const auto &vehicle : vehicles)
    {
        lines.push_back(FileManager::join({std::to_string(vehicle.getId()), vehicle.getVehicleNumber(), vehicle.getBrand(), vehicle.getModel(), vehicle.getType(), std::to_string(vehicle.getManufacturingYear()), vehicle.getColor(), vehicle.getFuelType(), vehicle.getTransmission(), std::to_string(vehicle.getSeatingCapacity()), std::to_string(vehicle.getPricePerDay()), std::to_string(vehicle.getMileage()), vehicle.getStatus()}, '|'));
    }
    FileManager::writeLines(kVehiclesPath, lines);
}

void RentalSystem::addVehicle()
{
    std::string vehicleNumber = utils::getNonEmptyString("Vehicle number: ");
    std::string brand = utils::getNonEmptyString("Brand: ");
    std::string model = utils::getNonEmptyString("Model: ");
    std::string type = utils::getNonEmptyString("Type: ");
    int year = utils::getInt("Manufacturing year: ");
    std::string color = utils::getNonEmptyString("Color: ");
    std::string fuelType = utils::getNonEmptyString("Fuel type: ");
    std::string transmission = utils::getNonEmptyString("Transmission: ");
    int seatingCapacity = utils::getInt("Seating capacity: ");
    double pricePerDay = utils::getDouble("Price per day: ");
    double mileage = utils::getDouble("Mileage: ");

    vehicles.emplace_back(nextVehicleId++, vehicleNumber, brand, model, type, year, color, fuelType, transmission, seatingCapacity, pricePerDay, mileage, "AVAILABLE");
    saveVehicles();
    std::cout << "[SUCCESS] Vehicle added successfully.\n";
}
void RentalSystem::viewVehicles()
{
    if (vehicles.empty())
    {
        utils::printWarning("No vehicles found.");
        return;
    }

    utils::printHeader("AVAILABLE VEHICLES");

    std::vector<std::vector<std::string>> rows;

    for (const auto &vehicle : vehicles)
    {
        rows.push_back({std::to_string(vehicle.getId()),
                        vehicle.getVehicleNumber(),
                        vehicle.getBrand(),
                        vehicle.getModel(),
                        vehicle.getType(),
                        utils::formatMoney(vehicle.getPricePerDay()),
                        vehicle.getStatus()});
    }

    utils::printTable(
        {"ID", "Vehicle Number", "Brand", "Model",
         "Type", "Price/Day", "Status"},
        rows);
}

void RentalSystem::browseVehicles()
{
    viewVehicles();
}
void RentalSystem::removeVehicle()
{

    if (vehicles.empty())
    {
        utils::printWarning("No vehicles available to remove.");
        return;
    }

    utils::printHeader("REMOVE VEHICLE");

    // Show existing vehicles
    std::vector<std::vector<std::string>> rows;

    for (const auto &vehicle : vehicles)
    {
        rows.push_back({std::to_string(vehicle.getId()),
                        vehicle.getVehicleNumber(),
                        vehicle.getBrand(),
                        vehicle.getModel(),
                        vehicle.getType(),
                        utils::formatMoney(vehicle.getPricePerDay()),
                        vehicle.getStatus()});
    }

    utils::printTable(
        {"ID",
         "Vehicle Number",
         "Brand",
         "Model",
         "Type",
         "Price/Day",
         "Status"},
        rows);

    std::cout << "\n";

    // Ask for vehicle ID
    int vehicleId = utils::getInt(
        "Enter Vehicle ID to remove: ");

    // Ask for vehicle number
    std::string vehicleNumber =
        utils::getNonEmptyString(
            "Enter Vehicle Number to confirm: ");

    // Find vehicle
    auto it = std::find_if(
        vehicles.begin(),
        vehicles.end(),
        [&](const Vehicle &vehicle)
        {
            return vehicle.getId() == vehicleId &&
                   vehicle.getVehicleNumber() == vehicleNumber;
        });

    // Vehicle not found or details don't match
    if (it == vehicles.end())
    {

        utils::printError(
            "Vehicle ID and Vehicle Number do not match.");

        return;
    }

    // Don't allow removal of currently booked vehicle
    if (it->getStatus() == "BOOKED")
    {

        utils::printError(
            "This vehicle is currently booked and cannot be removed.");

        return;
    }

    // Confirmation
    std::cout << "\n";
    std::cout << "Vehicle selected for removal:\n";
    std::cout << "ID     : " << it->getId() << "\n";
    std::cout << "Number : " << it->getVehicleNumber() << "\n";
    std::cout << "Brand  : " << it->getBrand() << "\n";
    std::cout << "Model  : " << it->getModel() << "\n";

    std::string confirmation =
        utils::getNonEmptyString(
            "\nAre you sure you want to remove this vehicle? (YES/NO): ");

    if (confirmation != "YES" &&
        confirmation != "yes")
    {

        utils::printWarning(
            "Vehicle removal cancelled.");

        return;
    }

    // Remove vehicle from vector
    vehicles.erase(it);

    // Save updated vehicle list
    saveVehicles();

    utils::printSuccess(
        "Vehicle removed successfully.");
}

void RentalSystem::loadBookings()
{
    bookings.clear();
    auto lines = FileManager::readLines(kBookingsPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 11)
        {
            try
            {
                int id = std::stoi(parts[0]);
                int customerId = std::stoi(parts[1]);
                int vehicleId = std::stoi(parts[2]);
                Date pickupDate = Date::parse(parts[3]);
                Date returnDate = Date::parse(parts[4]);
                std::string couponCode = "";
                double discountAmount = 0.0;

                if (parts.size() > 22)
                {
                    couponCode = parts[22];
                }

                if (parts.size() > 23)
                {
                    discountAmount = std::stod(parts[23]);
                }

                Booking booking(
                    id,
                    customerId,
                    vehicleId,
                    pickupDate,
                    returnDate,
                    parts[5],
                    parts[6],
                    std::stoi(parts[7]),
                    std::stod(parts[8]),
                    parts[9],
                    Date::parse(parts[10]),
                    couponCode,
                    discountAmount);
                // Booking booking(id, customerId, vehicleId, pickupDate, returnDate, parts[5], parts[6], std::stoi(parts[7]), std::stod(parts[8]), parts[9], Date::parse(parts[10]));
                if (parts.size() > 11)
                {
                    booking.setPickupCondition(parts[11]);
                }
                if (parts.size() > 12)
                {
                    booking.setOdometerAtPickup(std::stoi(parts[12]));
                }
                if (parts.size() > 13)
                {
                    booking.setFuelAtPickup(std::stoi(parts[13]));
                }
                if (parts.size() > 14)
                {
                    booking.setReturnCondition(parts[14]);
                }
                if (parts.size() > 15)
                {
                    booking.setOdometerAtReturn(std::stoi(parts[15]));
                }
                if (parts.size() > 16)
                {
                    booking.setFuelAtReturn(std::stoi(parts[16]));
                }
                if (parts.size() > 17)
                {
                    booking.setDamageInfo(parts[17]);
                }
                if (parts.size() > 18)
                {
                    booking.setLateDays(std::stoi(parts[18]));
                }
                if (parts.size() > 19)
                {
                    booking.setLateFee(std::stod(parts[19]));
                }
                if (parts.size() > 20)
                {
                    booking.setFuelCharge(std::stod(parts[20]));
                }
                if (parts.size() > 21)
                {
                    booking.setDamageCharge(std::stod(parts[21]));
                }
                bookings.push_back(booking);
                if (id >= nextBookingId)
                {
                    nextBookingId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}
bool RentalSystem::isVehicleAvailable(
    int vehicleId,
    const Date &pickup,
    const Date &returnDate) const
{

    // Invalid date range
    if (!pickup.isValid() ||
        !returnDate.isValid() ||
        !(pickup < returnDate))
    {

        return false;
    }

    // Check every existing booking
    for (const auto &booking : bookings)
    {

        // Different vehicle
        if (booking.getVehicleId() != vehicleId)
        {
            continue;
        }

        // Cancelled bookings don't block the vehicle
        if (booking.getStatus() == "CANCELLED")
        {
            continue;
        }

        // Completed bookings don't block future rentals
        if (booking.getStatus() == "COMPLETED")
        {
            continue;
        }

        Date existingPickup =
            booking.getPickupDate();

        Date existingReturn =
            booking.getReturnDate();

        /*
         * Two rental periods overlap when:
         *
         * New pickup < Existing return
         * AND
         * New return > Existing pickup
         */

        if (pickup < existingReturn &&
            returnDate > existingPickup)
        {

            return false;
        }
    }

    return true;
}
void RentalSystem::saveBookings()
{
    std::vector<std::string> lines;
    for (const auto &booking : bookings)
    {
        lines.push_back(FileManager::join({std::to_string(booking.getId()), std::to_string(booking.getCustomerId()), std::to_string(booking.getVehicleId()), booking.getPickupDate().toString(), booking.getReturnDate().toString(), booking.getPickupLocation(), booking.getReturnLocation(), std::to_string(booking.getRentalDays()), std::to_string(booking.getRentalPrice()), booking.getStatus(), booking.getCreatedDate().toString(), booking.getPickupCondition(), std::to_string(booking.getOdometerAtPickup()), std::to_string(booking.getFuelAtPickup()), booking.getReturnCondition(), std::to_string(booking.getOdometerAtReturn()), std::to_string(booking.getFuelAtReturn()), booking.getDamageInfo(), std::to_string(booking.getLateDays()), std::to_string(booking.getLateFee()), std::to_string(booking.getFuelCharge()), std::to_string(booking.getDamageCharge()), booking.getCouponCode(),
                                           std::to_string(booking.getDiscountAmount())},
                                          '|'));
    }
    FileManager::writeLines(kBookingsPath, lines);
}

void RentalSystem::loadPayments()
{
    payments.clear();
    auto lines = FileManager::readLines(kPaymentsPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 8)
        {
            try
            {
                int id = std::stoi(parts[0]);
                payments.emplace_back(id, std::stoi(parts[1]), std::stoi(parts[2]), std::stod(parts[3]), parts[4], parts[5], parts[6], parts[7]);
                if (id >= nextPaymentId)
                {
                    nextPaymentId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}

void RentalSystem::savePayments()
{
    std::vector<std::string> lines;
    for (const auto &payment : payments)
    {
        lines.push_back(FileManager::join({std::to_string(payment.getId()), std::to_string(payment.getBookingId()), std::to_string(payment.getCustomerId()), std::to_string(payment.getAmount()), payment.getMethod(), payment.getPaymentDate(), payment.getTransactionId(), payment.getStatus()}, '|'));
    }
    FileManager::writeLines(kPaymentsPath, lines);
}

void RentalSystem::loadMaintenance()
{
    maintenanceRecords.clear();
    auto lines = FileManager::readLines(kMaintenancePath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 7)
        {
            try
            {
                int id = std::stoi(parts[0]);
                maintenanceRecords.emplace_back(id, std::stoi(parts[1]), parts[2], Date::parse(parts[3]), std::stod(parts[4]), parts[5], Date::parse(parts[6]));
                if (id >= nextMaintenanceId)
                {
                    nextMaintenanceId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}

void RentalSystem::saveMaintenance()
{
    std::vector<std::string> lines;
    for (const auto &maintenance : maintenanceRecords)
    {
        lines.push_back(FileManager::join({std::to_string(maintenance.getId()), std::to_string(maintenance.getVehicleId()), maintenance.getServiceType(), maintenance.getServiceDate().toString(), std::to_string(maintenance.getCost()), maintenance.getDescription(), maintenance.getNextServiceDate().toString()}, '|'));
    }
    FileManager::writeLines(kMaintenancePath, lines);
}

void RentalSystem::loadReviews()
{
    reviews.clear();
    auto lines = FileManager::readLines(kReviewsPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 6)
        {
            try
            {
                int id = std::stoi(parts[0]);
                reviews.emplace_back(id, std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]), parts[4], Date::parse(parts[5]));
                if (id >= nextReviewId)
                {
                    nextReviewId = id + 1;
                }
            }
            catch (...)
            {
                continue;
            }
        }
    }
}

void RentalSystem::saveReviews()
{
    std::vector<std::string> lines;
    for (const auto &review : reviews)
    {
        lines.push_back(FileManager::join({std::to_string(review.getId()), std::to_string(review.getCustomerId()), std::to_string(review.getVehicleId()), std::to_string(review.getRating()), review.getComment(), review.getReviewDate().toString()}, '|'));
    }
    FileManager::writeLines(kReviewsPath, lines);
}

void RentalSystem::createBooking()
{
    if (currentUser == nullptr)
    {
        std::cout << "[ERROR] Please login as a customer first.\n";
        return;
    }

    viewVehicles();
    int vehicleId = utils::getInt("Enter vehicle ID: ");

    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                  { return vehicle.getId() == vehicleId; });
    if (vehicleIt == vehicles.end())
    {
        std::cout << "[ERROR] Vehicle not found.\n";
        return;
    }

    try
    {
        Date pickup = Date::parse(utils::getNonEmptyString("Pickup date (DD-MM-YYYY): "));
        Date returnDate = Date::parse(utils::getNonEmptyString("Return date (DD-MM-YYYY): "));
        if (!isVehicleAvailable(vehicleId, pickup, returnDate))
        {
            std::cout << "[ERROR] Vehicle is not available for the selected dates.\n";
            return;
        }

        std::string pickupLocation = utils::getNonEmptyString("Pickup location: ");
        std::string returnLocation = utils::getNonEmptyString("Return location: ");
        int rentalDays = Date::daysBetween(pickup, returnDate);

       
        double baseRentalPrice =
            rentalDays * vehicleIt->getPricePerDay();

        double discount = 0.0;
        std::string couponCode = "";

        if (!coupons.empty())
        {

            std::cout << "\n";
            std::cout << "----------------------------------------\n";
            std::cout << "COUPON\n";
            std::cout << "----------------------------------------\n";

            std::string enteredCode =
                utils::getNonEmptyString(
                    "Coupon code (enter NONE to skip): ");

            if (enteredCode != "NONE" &&
                enteredCode != "none")
            {

                bool couponFound = false;

                Date today =
                    Date::parse(currentDateString());

                for (const auto &coupon : coupons)
                {

                    if (coupon.getCode() == enteredCode)
                    {

                        couponFound = true;

                        if (!coupon.isValidFor(
                                baseRentalPrice,
                                today))
                        {

                            utils::printError(
                                "Coupon is expired, inactive, "
                                "usage limit reached, or minimum "
                                "amount is not satisfied.");

                            return;
                        }

                        discount =
                            coupon.calculateDiscount(
                                baseRentalPrice);

                        if (discount <= 0.0)
                        {

                            utils::printError(
                                "Coupon did not provide a discount.");

                            return;
                        }

                        couponCode =
                            coupon.getCode();

                        break;
                    }
                }

                if (!couponFound)
                {

                    utils::printError(
                        "Invalid coupon code.");

                    return;
                }
            }
        }

        double finalRentalPrice =
            baseRentalPrice - discount;

        bookings.emplace_back(
            nextBookingId++,
            currentUser->getId(),
            vehicleId,
            pickup,
            returnDate,
            pickupLocation,
            returnLocation,
            rentalDays,
            finalRentalPrice,
            "BOOKED",
            Date::parse(currentDateString()),
            couponCode,
            discount);

        auto vehicleIt = std::find_if(
            vehicles.begin(),
            vehicles.end(),
            [&](const Vehicle &vehicle)
            {
                return vehicle.getId() == vehicleId;
            });

        if (vehicleIt != vehicles.end())
        {
            vehicleIt->setStatus("BOOKED");
            saveVehicles();
        }

        // Update coupon usage
        if (!couponCode.empty())
        {
            for (auto &coupon : coupons)
            {
                if (coupon.getCode() == couponCode)
                {
                    coupon.incrementUsage();
                    break;
                }
            }

            saveCoupons();
        }

        saveBookings();
        if (!couponCode.empty())
        {

            for (auto &coupon : coupons)
            {

                if (coupon.getCode() == couponCode)
                {

                    coupon.incrementUsage();
                    break;
                }
            }

            saveCoupons();
        }
        saveBookings();
        if (!couponCode.empty())
        {

            for (auto &coupon : coupons)
            {

                if (coupon.getCode() == couponCode)
                {

                    coupon.incrementUsage();
                    break;
                }
            }

            saveCoupons();
        }

        saveBookings();

        // ===== BOOKING SUCCESS MESSAGE =====

        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "        BOOKING CREATED SUCCESSFULLY\n";
        std::cout << "========================================\n";

        std::cout << "Base Rental   : Rs. "
                  << utils::formatMoney(baseRentalPrice)
                  << "\n";

        if (!couponCode.empty())
        {

            std::cout << "Coupon        : "
                      << couponCode
                      << "\n";

            std::cout << "Discount      : Rs. "
                      << utils::formatMoney(discount)
                      << "\n";
        }

        std::cout << "Final Rental  : Rs. "
                  << utils::formatMoney(finalRentalPrice)
                  << "\n";

        std::cout << "========================================\n";
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "[ERROR] Invalid date format.\n";
    }
}
void RentalSystem::viewBookings()
{
    if (bookings.empty())
    {
        std::cout << "No bookings found.\n";
        return;
    }

    for (const auto &booking : bookings)
    {
        if (currentUser != nullptr && booking.getCustomerId() != currentUser->getId())
        {
            continue;
        }
        std::cout << "Booking ID: " << booking.getId() << " | Vehicle ID: " << booking.getVehicleId() << " | Status: " << booking.getStatus() << " | Dates: " << booking.getPickupDate().toString() << " to " << booking.getReturnDate().toString() << "\n";
    }
}

void RentalSystem::cancelBooking()
{
    int bookingId = utils::getInt("Booking ID: ");
    auto it = std::find_if(bookings.begin(), bookings.end(), [&](const Booking &booking)
                           { return booking.getId() == bookingId; });
    if (it == bookings.end())
    {
        std::cout << "[ERROR] Booking not found.\n";
        return;
    }
    if (currentUser != nullptr && it->getCustomerId() != currentUser->getId())
    {
        std::cout << "[ERROR] You can only cancel your own bookings.\n";
        return;
    }
    it->setStatus("CANCELLED");

    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                  { return vehicle.getId() == it->getVehicleId(); });
    if (vehicleIt != vehicles.end())
    {
        vehicleIt->setStatus("AVAILABLE");
        saveVehicles();
    }

    saveBookings();
    addNotification("Booking #" + std::to_string(bookingId) + " was cancelled.", "BOOKING");
    std::cout << "[SUCCESS] Booking cancelled.\n";
}

void RentalSystem::processPickup()
{
    int bookingId = utils::getInt("Booking ID: ");
    auto it = std::find_if(bookings.begin(), bookings.end(), [&](const Booking &booking)
                           { return booking.getId() == bookingId; });
    if (it == bookings.end())
    {
        std::cout << "[ERROR] Booking not found.\n";
        return;
    }
    if (it->getStatus() != "BOOKED" && it->getStatus() != "CONFIRMED")
    {
        std::cout << "[ERROR] Booking is not ready for pickup.\n";
        return;
    }

    std::string condition = utils::getNonEmptyString("Vehicle condition: ");
    int odometer = utils::getInt("Odometer reading: ");
    int fuel = utils::getInt("Fuel level (%): ");
    it->setPickupCondition(condition);
    it->setOdometerAtPickup(odometer);
    it->setFuelAtPickup(fuel);
    it->setStatus("PICKED_UP");

    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                  { return vehicle.getId() == it->getVehicleId(); });
    if (vehicleIt != vehicles.end())
    {
        vehicleIt->setStatus("RENTED");
        saveVehicles();
    }
    saveBookings();
    std::cout << "[SUCCESS] Pickup processed.\n";
}

void RentalSystem::processReturn()
{
    int bookingId = utils::getInt("Booking ID: ");
    auto it = std::find_if(bookings.begin(), bookings.end(), [&](const Booking &booking)
                           { return booking.getId() == bookingId; });
    if (it == bookings.end())
    {
        std::cout << "[ERROR] Booking not found.\n";
        return;
    }
    if (it->getStatus() != "PICKED_UP")
    {
        std::cout << "[ERROR] Booking is not currently rented.\n";
        return;
    }

    try
    {
        Date actualReturn = Date::parse(utils::getNonEmptyString("Actual return date (DD-MM-YYYY): "));
        std::string condition = utils::getNonEmptyString("Vehicle condition: ");
        int odometer = utils::getInt("Odometer reading: ");
        int fuel = utils::getInt("Fuel level (%): ");
        std::string damageInfo = utils::getNonEmptyString("Damage information (none if none): ");
        double damageCharge = 0.0;
        if (damageInfo != "none")
        {
            damageCharge = utils::getDouble("Damage charge: ");
        }

        int lateDays = 0;
        if (actualReturn > it->getReturnDate())
        {
            lateDays = std::max(0, Date::daysBetween(it->getReturnDate(), actualReturn) - 1);
        }
        double lateFee = lateDays * 1000.0;
        double fuelCharge = 0.0;
        if (fuel < it->getFuelAtPickup())
        {
            fuelCharge = (it->getFuelAtPickup() - fuel) * 100.0;
        }

        it->setReturnCondition(condition);
        it->setOdometerAtReturn(odometer);
        it->setFuelAtReturn(fuel);
        it->setDamageInfo(damageInfo);
        it->setLateDays(lateDays);
        it->setLateFee(lateFee);
        it->setFuelCharge(fuelCharge);
        it->setDamageCharge(damageCharge);
        it->setStatus("COMPLETED");

        auto customerIt = std::find_if(users.begin(), users.end(), [&](const User &user)
                                       { return user.getId() == it->getCustomerId(); });
        if (customerIt != users.end())
        {
            customerIt->incrementRentals();
            customerIt->incrementCompletedRentals();
            customerIt->addToTotalSpent(it->getRentalPrice() + lateFee + fuelCharge + damageCharge);
            const int earnedPoints = static_cast<int>((it->getRentalPrice() + lateFee + fuelCharge + damageCharge) / 100.0);
            customerIt->addLoyaltyPoints(earnedPoints);
            int newPoints = customerIt->getLoyaltyPoints();
            if (newPoints >= 2500)
            {
                customerIt->setMembershipLevel("PLATINUM");
            }
            else if (newPoints >= 1000)
            {
                customerIt->setMembershipLevel("GOLD");
            }
            else if (newPoints >= 500)
            {
                customerIt->setMembershipLevel("SILVER");
            }
            else
            {
                customerIt->setMembershipLevel("BRONZE");
            }
        }

        auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                      { return vehicle.getId() == it->getVehicleId(); });
        if (vehicleIt != vehicles.end())
        {
            vehicleIt->setStatus("AVAILABLE");
            saveVehicles();
        }
        saveUsers();
        saveBookings();
        addNotification("Vehicle returned for booking #" + std::to_string(bookingId) + ".", "BOOKING");
        std::cout << "[SUCCESS] Return processed.\n";
    }
    catch (const std::exception &ex)
    {
        std::cout << "[ERROR] " << ex.what() << "\n";
    }
}


void RentalSystem::makePayment()
{
    if (currentUser == nullptr)
    {
        utils::printError("Please login as a customer first.");
        return;
    }

    int bookingId = utils::getInt("Booking ID: ");

    auto bookingIt = std::find_if(
        bookings.begin(),
        bookings.end(),
        [&](const Booking &booking)
        {
            return booking.getId() == bookingId &&
                   booking.getCustomerId() == currentUser->getId();
        });

    if (bookingIt == bookings.end())
    {
        utils::printError("Booking not found or does not belong to you.");
        return;
    }

    if (bookingIt->getStatus() != "COMPLETED")
    {
        utils::printError(
            "Payment can only be made after the vehicle has been returned.");
        return;
    }

    // Check if payment already exists
    auto existingPayment = std::find_if(
        payments.begin(),
        payments.end(),
        [&](const Payment &payment)
        {
            return payment.getBookingId() == bookingId &&
                   payment.getStatus() == "PAID";
        });

    if (existingPayment != payments.end())
    {
        utils::printWarning("This booking has already been paid.");
        return;
    }

    double totalAmount =
        bookingIt->getRentalPrice() +
        bookingIt->getLateFee() +
        bookingIt->getFuelCharge() +
        bookingIt->getDamageCharge();

    utils::printHeader("PAYMENT");

    std::cout << "Booking ID    : BK"
              << bookingId << "\n";

    std::cout << "Rental Cost   : Rs. "
              << utils::formatMoney(
                     bookingIt->getRentalPrice())
              << "\n";

    std::cout << "Late Fee      : Rs. "
              << utils::formatMoney(
                     bookingIt->getLateFee())
              << "\n";

    std::cout << "Fuel Charge   : Rs. "
              << utils::formatMoney(
                     bookingIt->getFuelCharge())
              << "\n";

    std::cout << "Damage Charge : Rs. "
              << utils::formatMoney(
                     bookingIt->getDamageCharge())
              << "\n";

    std::cout << "----------------------------------------\n";

    std::cout << "TOTAL AMOUNT  : Rs. "
              << utils::formatMoney(totalAmount)
              << "\n";

    std::string method =
        utils::getNonEmptyString(
            "Payment method (Cash/eSewa/Khalti/Card): ");

    double amount =
        utils::getDouble("Enter payment amount: ");

    if (amount < totalAmount)
    {
        utils::printError(
            "Payment amount is less than the total amount.");
        return;
    }

    // Generate payment ID
    int paymentId = nextPaymentId++;

    // Generate transaction ID
    std::string transactionId =
        "TXN" + std::to_string(paymentId);

    Payment payment(
        paymentId,
        bookingIt->getId(),
        bookingIt->getCustomerId(),
        totalAmount,
        method,
        currentDateString(),
        transactionId,
        "PAID");

    // Add payment to memory
    payments.push_back(payment);

    // Save payment permanently
    savePayments();

    utils::printSuccess(
        "Payment completed successfully.");

    std::cout << "Transaction ID: "
              << transactionId << "\n";

    // Generate invoice
    generateInvoice(*bookingIt, payment);
}
void RentalSystem::generateInvoice(
    const Booking &booking,
    const Payment &payment)
{
    auto vehicleIt = std::find_if(
        vehicles.begin(),
        vehicles.end(),
        [&](const Vehicle &vehicle)
        {
            return vehicle.getId() == booking.getVehicleId();
        });

    if (vehicleIt == vehicles.end())
    {
        utils::printError("Vehicle information not found.");
        return;
    }

    auto customerIt = std::find_if(
        users.begin(),
        users.end(),
        [&](const User &user)
        {
            return user.getId() == booking.getCustomerId();
        });

    if (customerIt == users.end())
    {
        utils::printError("Customer information not found.");
        return;
    }

    Invoice invoice(
        booking,
        *vehicleIt,
        *customerIt,
        payment);

    utils::printHeader("INVOICE");

    invoice.display();

    utils::printSuccess(
        "Invoice generated successfully.");
}
void RentalSystem::viewInvoice()
{
    if (currentUser == nullptr)
    {
        utils::printError("Please login as a customer first.");
        return;
    }

    std::vector<const Payment *> customerPayments;

    for (const auto &payment : payments)
    {
        if (payment.getCustomerId() == currentUser->getId() &&
            payment.getStatus() == "PAID")
        {

            customerPayments.push_back(&payment);
        }
    }

    if (customerPayments.empty())
    {
        utils::printInfo(
            "You do not have any paid invoices yet.");
        return;
    }

    utils::printHeader("MY INVOICES");

    for (size_t i = 0; i < customerPayments.size(); ++i)
    {

        const Payment *payment =
            customerPayments[i];

        std::cout
            << "[" << i + 1 << "] "
            << "Invoice: INV-BK"
            << payment->getBookingId()
            << " | Transaction: "
            << payment->getTransactionId()
            << " | Rs. "
            << utils::formatMoney(payment->getAmount())
            << "\n";
    }

    int choice =
        utils::getInt("Select invoice (0 to cancel): ");

    if (choice == 0)
    {
        return;
    }

    if (choice < 1 ||
        choice > static_cast<int>(customerPayments.size()))
    {

        utils::printError("Invalid invoice selection.");
        return;
    }

    const Payment *selectedPayment =
        customerPayments[choice - 1];

    auto bookingIt = std::find_if(
        bookings.begin(),
        bookings.end(),
        [&](const Booking &booking)
        {
            return booking.getId() ==
                       selectedPayment->getBookingId() &&
                   booking.getCustomerId() ==
                       currentUser->getId();
        });

    if (bookingIt == bookings.end())
    {
        utils::printError("Associated booking not found.");
        return;
    }

    generateInvoice(
        *bookingIt,
        *selectedPayment);
}

void RentalSystem::addMaintenance()
{
    int vehicleId = utils::getInt("Vehicle ID: ");
    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                  { return vehicle.getId() == vehicleId; });
    if (vehicleIt == vehicles.end())
    {
        std::cout << "[ERROR] Vehicle not found.\n";
        return;
    }

    std::string serviceType = utils::getNonEmptyString("Service type: ");
    double cost = utils::getDouble("Cost: ");
    std::string description = utils::getNonEmptyString("Description: ");
    std::string nextServiceDateInput = utils::getNonEmptyString("Next service date (DD-MM-YYYY): ");

    try
    {
        Date nextServiceDate = Date::parse(nextServiceDateInput);
        maintenanceRecords.emplace_back(nextMaintenanceId++, vehicleId, serviceType, Date::parse(currentDateString()), cost, description, nextServiceDate);
        vehicleIt->setStatus("MAINTENANCE");
        saveMaintenance();
        saveVehicles();
        std::cout << "[SUCCESS] Maintenance record added.\n";
    }
    catch (const std::exception &ex)
    {
        std::cout << "[ERROR] " << ex.what() << "\n";
    }
}

void RentalSystem::viewMaintenance()
{
    if (maintenanceRecords.empty())
    {
        std::cout << "No maintenance records found.\n";
        return;
    }
    for (const auto &maintenance : maintenanceRecords)
    {
        std::cout << "Maintenance ID: " << maintenance.getId() << " | Vehicle ID: " << maintenance.getVehicleId() << " | Type: " << maintenance.getServiceType() << "\n";
    }
}

void RentalSystem::addReview()
{
    if (currentUser == nullptr)
    {
        std::cout << "[ERROR] Please login as a customer first.\n";
        return;
    }

    int vehicleId = utils::getInt("Vehicle ID: ");
    int rating = utils::getInt("Rating (1-5): ");
    if (rating < 1 || rating > 5)
    {
        std::cout << "[ERROR] Rating must be between 1 and 5.\n";
        return;
    }
    std::string comment = utils::getNonEmptyString("Comment: ");
    reviews.emplace_back(nextReviewId++, currentUser->getId(), vehicleId, rating, comment, Date::parse(currentDateString()));
    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                  { return vehicle.getId() == vehicleId; });
    if (vehicleIt != vehicles.end())
    {
        vehicleIt->addRating(rating);
    }
    auto userIt = std::find_if(users.begin(), users.end(), [&](const User &user)
                               { return user.getId() == currentUser->getId(); });
    if (userIt != users.end())
    {
        userIt->setAverageRating((userIt->getAverageRating() + rating) / 2.0);
    }
    saveReviews();
    saveVehicles();
    saveUsers();
    std::cout << "[SUCCESS] Review added.\n";
}

void RentalSystem::showReports()
{
    Report report(vehicles, users, bookings);
    report.showDashboardSummary();
    report.showRevenueAnalytics();
    report.showPopularVehicles();
    report.showVehicleSummary();
    report.showCustomerSummary();
    report.showFinancialSummary();
}

void RentalSystem::loadCoupons()
{
    coupons.clear();
    auto lines = FileManager::readLines(kCouponsPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 9)
        {
            try
            {
                coupons.emplace_back(std::stoi(parts[0]), parts[1], parts[2], std::stod(parts[3]), std::stod(parts[4]), Date::parse(parts[5]), std::stoi(parts[6]), std::stoi(parts[7]), parts[8] == "1");
            }
            catch (...)
            {
            }
        }
    }
}

void RentalSystem::saveCoupons()
{
    std::vector<std::string> lines;
    for (const auto &coupon : coupons)
    {
        lines.push_back(FileManager::join({std::to_string(coupon.getId()), coupon.getCode(), coupon.getDiscountType(), std::to_string(coupon.getDiscountValue()), std::to_string(coupon.getMinAmount()), coupon.getExpiryDate().toString(), std::to_string(coupon.getMaxUsage()), std::to_string(coupon.getCurrentUsage()), coupon.isActive() ? "1" : "0"}, '|'));
    }
    FileManager::writeLines(kCouponsPath, lines);
}

void RentalSystem::loadNotifications()
{
    notifications.clear();
    auto lines = FileManager::readLines(kNotificationsPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 4)
        {
            try
            {
                notifications.emplace_back(std::stoi(parts[0]), parts[1], parts[2], parts[3] == "1");
            }
            catch (...)
            {
            }
        }
    }
}

void RentalSystem::saveNotifications()
{
    std::vector<std::string> lines;
    for (const auto &notification : notifications)
    {
        lines.push_back(FileManager::join({std::to_string(notification.getId()), notification.getMessage(), notification.getType(), notification.isRead() ? "1" : "0"}, '|'));
    }
    FileManager::writeLines(kNotificationsPath, lines);
}

void RentalSystem::loadFavorites()
{
    favorites.clear();
    auto lines = FileManager::readLines(kFavoritesPath);
    for (const std::string &line : lines)
    {
        auto parts = FileManager::split(line, '|');
        if (parts.size() >= 2)
        {
            try
            {
                favorites.emplace_back(std::stoi(parts[0]), std::stoi(parts[1]));
            }
            catch (...)
            {
            }
        }
    }
}

void RentalSystem::saveFavorites()
{
    std::vector<std::string> lines;
    for (const auto &favorite : favorites)
    {
        lines.push_back(FileManager::join({std::to_string(favorite.getCustomerId()), std::to_string(favorite.getVehicleId())}, '|'));
    }
    FileManager::writeLines(kFavoritesPath, lines);
}

void RentalSystem::addFavorite()
{
    if (currentUser == nullptr)
    {
        utils::printError("Please login first.");
        return;
    }
    int vehicleId = utils::getInt("Vehicle ID: ");
    if (isFavorite(vehicleId))
    {
        utils::printWarning("Vehicle already in favorites.");
        return;
    }
    favorites.emplace_back(currentUser->getId(), vehicleId);
    saveFavorites();
    utils::printSuccess("Vehicle added to favorites.");
}

void RentalSystem::removeFavorite()
{
    if (currentUser == nullptr)
    {
        return;
    }
    int vehicleId = utils::getInt("Vehicle ID: ");
    auto it = std::remove_if(favorites.begin(), favorites.end(), [&](const Favorite &favorite)
                             { return favorite.getCustomerId() == currentUser->getId() && favorite.getVehicleId() == vehicleId; });
    if (it != favorites.end())
    {
        favorites.erase(it, favorites.end());
        saveFavorites();
        utils::printSuccess("Vehicle removed from favorites.");
    }
    else
    {
        utils::printWarning("Favorite not found.");
    }
}

void RentalSystem::viewFavorites()
{
    if (currentUser == nullptr)
    {
        return;
    }
    utils::printHeader("FAVORITE VEHICLES");
    bool found = false;
    for (const auto &favorite : favorites)
    {
        if (favorite.getCustomerId() != currentUser->getId())
        {
            continue;
        }
        found = true;
        const auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                            { return vehicle.getId() == favorite.getVehicleId(); });
        if (vehicleIt != vehicles.end())
        {
            std::cout << vehicleIt->getBrand() << " " << vehicleIt->getModel() << "\n";
        }
    }
    if (!found)
    {
        utils::printInfo("You have no favorite vehicles yet.");
    }
}

void RentalSystem::showRecommendations()
{
    if (currentUser == nullptr)
    {
        return;
    }
    utils::printHeader("RECOMMENDED FOR YOU");
    utils::printInfo("Rule-based recommendations based on price, type, fuel, transmission, and availability.");
    std::vector<std::pair<int, int>> scored;
    for (const auto &vehicle : vehicles)
    {
        if (vehicle.getStatus() != "AVAILABLE")
        {
            continue;
        }
        int score = 0;
        score += vehicle.getType() == "Car" ? 2 : 0;
        if (vehicle.getFuelType() == "Petrol")
            score += 2;
        if (vehicle.getTransmission() == "Automatic")
            score += 1;
        if (vehicle.getSeatingCapacity() >= 4)
            score += 1;
        if (vehicle.getPricePerDay() <= 3500)
            score += 2;
        if (vehicle.getAverageRating() >= 4.0)
            score += 2;
        scored.push_back({vehicle.getId(), score});
    }
    std::sort(scored.begin(), scored.end(), [](const std::pair<int, int> &left, const std::pair<int, int> &right)
              { return left.second > right.second; });
    int count = 0;
    for (const auto &entry : scored)
    {
        if (count >= 3)
            break;
        const auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle &vehicle)
                                            { return vehicle.getId() == entry.first; });
        if (vehicleIt != vehicles.end())
        {
            std::cout << (count + 1) << ". " << vehicleIt->getBrand() << " " << vehicleIt->getModel()
                      << " | Score: " << entry.second << " | Rs. " << utils::formatMoney(vehicleIt->getPricePerDay()) << "\n";
        }
        ++count;
    }
}

bool RentalSystem::isFavorite(int vehicleId) const
{
    for (const auto &favorite : favorites)
    {
        if (favorite.getCustomerId() == currentUser->getId() && favorite.getVehicleId() == vehicleId)
        {
            return true;
        }
    }
    return false;
}

void RentalSystem::addCoupon()
{
    std::string code = utils::getNonEmptyString("Coupon code: ");
    std::string discountType = utils::getNonEmptyString("Discount type (PERCENT/FIXED): ");
    double discountValue = utils::getDouble("Discount value: ");
    double minAmount = utils::getDouble("Minimum amount: ");
    Date expiryDate = Date::parse(utils::getNonEmptyString("Expiry date (DD-MM-YYYY): "));
    int maxUsage = utils::getInt("Max usage: ");
    coupons.emplace_back(static_cast<int>(coupons.size()) + 1, code, discountType, discountValue, minAmount, expiryDate, maxUsage, 0, true);
    saveCoupons();
    utils::printSuccess("Coupon added.");
}

void RentalSystem::viewCoupons()
{
    if (coupons.empty())
    {
        utils::printWarning("No coupons found.");
        return;
    }
    utils::printHeader("COUPONS");
    for (const auto &coupon : coupons)
    {
        std::cout << coupon.getCode() << " | " << coupon.getDiscountType() << " " << coupon.getDiscountValue() << " | Min: " << coupon.getMinAmount() << " | Expiry: " << coupon.getExpiryDate().toString() << " | Usage: " << coupon.getCurrentUsage() << "/" << coupon.getMaxUsage() << "\n";
    }
}

void RentalSystem::manageCoupons()
{
    while (true)
    {
        utils::printHeader("COUPON MANAGEMENT");
        std::cout << "[1] View Coupons\n";
        std::cout << "[2] Add Coupon\n";
        std::cout << "[3] Back\n";
        int choice = utils::getInt("Enter choice: ");
        switch (choice)
        {
        case 1:
            viewCoupons();
            break;
        case 2:
            addCoupon();
            break;
        case 3:
            return;
        default:
            utils::printError("Invalid choice.");
        }
        utils::pauseScreen();
    }
}

void RentalSystem::viewNotifications()
{
    if (notifications.empty())
    {
        utils::printInfo("No notifications yet.");
        return;
    }
    utils::printHeader("NOTIFICATIONS");
    for (const auto &notification : notifications)
    {
        std::cout << (notification.isRead() ? "[READ]" : "[NEW]") << " " << notification.getMessage() << "\n";
    }
}

void RentalSystem::markNotificationRead()
{
    if (notifications.empty())
    {
        return;
    }
    viewNotifications();
    int id = utils::getInt("Enter notification ID to mark as read: ");
    for (auto &notification : notifications)
    {
        if (notification.getId() == id)
        {
            notification.markRead();
            saveNotifications();
            utils::printSuccess("Notification marked as read.");
            return;
        }
    }
    utils::printError("Notification not found.");
}

void RentalSystem::addNotification(const std::string &message, const std::string &type)
{
    notifications.emplace_back(static_cast<int>(notifications.size()) + 1, message, type, false);
    saveNotifications();
}

void RentalSystem::showCouponMenu()
{
    while (true)
    {
        utils::printHeader("COUPON CENTER");
        std::cout << "[1] View Coupons\n";
        std::cout << "[2] Back\n";
        int choice = utils::getInt("Enter choice: ");
        switch (choice)
        {
        case 1:
            viewCoupons();
            break;
        case 2:
            return;
        default:
            utils::printError("Invalid choice.");
        }
        utils::pauseScreen();
    }
}

void RentalSystem::manageFavorites()
{
    if (currentUser == nullptr)
    {
        utils::printError("Please login first.");
        return;
    }

    while (true)
    {
        utils::printHeader("FAVORITE VEHICLES");
        std::cout << "[1] Add Favorite\n";
        std::cout << "[2] Remove Favorite\n";
        std::cout << "[3] View Favorites\n";
        std::cout << "[4] Back\n";
        int choice = utils::getInt("Enter choice: ");
        switch (choice)
        {
        case 1:
            addFavorite();
            break;
        case 2:
            removeFavorite();
            break;
        case 3:
            viewFavorites();
            break;
        case 4:
            return;
        default:
            utils::printError("Invalid choice.");
        }
        if (choice != 4)
        {
            utils::pauseScreen();
        }
    }
}

void RentalSystem::manageNotifications()
{
    while (true)
    {
        utils::printHeader("NOTIFICATIONS");
        std::cout << "[1] View Notifications\n";
        std::cout << "[2] Mark Notification as Read\n";
        std::cout << "[3] Back\n";
        int choice = utils::getInt("Enter choice: ");
        switch (choice)
        {
        case 1:
            viewNotifications();
            break;
        case 2:
            markNotificationRead();
            break;
        case 3:
            return;
        default:
            utils::printError("Invalid choice.");
        }
        if (choice != 3)
        {
            utils::pauseScreen();
        }
    }
}

void RentalSystem::showAdminDashboard()
{
    while (true)
    {
        utils::clearScreen();
        utils::printHeader("ADMIN DASHBOARD");
       
        std::cout << "\n";
        std::cout << "============================================================\n";
        std::cout << "                    WELCOME ADMINISTRATOR\n";
        std::cout << "============================================================\n";
        std::cout << "\n";

        std::cout << "   [1] Add Vehicle                 [6] Show Reports\n";
        std::cout << "   [2] View Vehicles               [7] Coupon Management\n";
        std::cout << "   [3] Remove Vehicle              [8] Notifications\n";
        std::cout << "   [4] View Bookings               [9] Logout\n";
        std::cout << "   [5] Add Maintenance\n";

        std::cout << "\n";
        std::cout << "============================================================\n";

        int choice = utils::getInt("Enter choice: ");

        switch (choice)
        {
        case 1:
            addVehicle();
            break;
        case 2:
            viewVehicles();
            break;
        case 3:
            removeVehicle();
            break;
        case 4:
            viewBookings();
            break;
        case 5:
            addMaintenance();
            break;
        case 6:
            showReports();
            break;
        case 7:
            manageCoupons();
            break;
        case 8:
            manageNotifications();
            break;
        case 9:
            utils::printSuccess("Logged out.");
            return;
        default:
            utils::printError("Invalid choice.");
        }
        if (choice != 9)
        {
            utils::pauseScreen();
        }
    }
}

void RentalSystem::showCustomerDashboard()
{
    while (true)
    {
        utils::clearScreen();

               utils::printHeader("CUSTOMER DASHBOARD");

        std::cout << "\n";

        std::cout << "   [1]  Browse Vehicles              [9]  View Invoice\n";
        std::cout << "   [2]  Create Booking               [10] Add Favorite Vehicles\n";
        std::cout << "   [3]  Smart Vehicle Availability   [11] View Favorite Vehicles\n";
        std::cout << "   [4]  My Bookings                  [12] Coupons\n";
        std::cout << "   [5]  Cancel Booking               [13] Notifications\n";
        std::cout << "   [6]  Process Pickup               [14] Review Vehicle\n";
        std::cout << "   [7]  Return Vehicle               [15] Logout\n";
        std::cout << "   [8]  Make Payment\n";

        std::cout << "\n";

        int choice = utils::getInt("Enter choice: ");

        switch (choice)
        {

        case 1:
            browseVehicles();
            break;

        case 2:
            createBooking();
            break;

        case 3:
            smartVehicleAvailability();
            break;

        case 4:
            viewBookings();
            break;

        case 5:
            cancelBooking();
            break;

        case 6:
            processPickup();
            break;

        case 7:
            processReturn();
            break;

        case 8:
            makePayment();
            break;

        case 9:
            viewInvoice();
            break;

        case 10:
            addFavorite();
            break;

        case 11:
            viewFavorites();
            break;

        case 12:
            showCouponMenu();
            break;

        case 13:
            viewNotifications();
            break;

        case 14:
            addReview();
            break;

        case 15:
            utils::printSuccess(
                "Logged out.");
            return;

        default:
            utils::printError(
                "Invalid choice.");
        }

        if (choice != 15)
        {
            utils::pauseScreen();
        }
    }
}

bool RentalSystem::isUsernameTaken(const std::string &username) const
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}

bool RentalSystem::authenticate(const std::string &username, const std::string &password, std::string &role) const
{
    if (username == "admin" && password == "admin123")
    {
        role = "admin";
        return true;
    }
    for (const auto &user : users)
    {
        if (user.getUsername() == username && user.getPassword() == password)
        {
            role = user.getRole();
            return true;
        }
    }
    return false;
}

void RentalSystem::smartVehicleAvailability()
{

    utils::printHeader(
        "SMART VEHICLE AVAILABILITY");

    std::string pickupInput =
        utils::getNonEmptyString(
            "Pickup Date (DD-MM-YYYY): ");

    std::string returnInput =
        utils::getNonEmptyString(
            "Return Date (DD-MM-YYYY): ");

    Date pickupDate;
    Date returnDate;

    try
    {

        pickupDate = Date::parse(pickupInput);
        returnDate = Date::parse(returnInput);
    }
    catch (const std::exception &e)
    {

        utils::printError(
            "Invalid date. Please use DD-MM-YYYY.");

        return;
    }

    // Return date must be after pickup date
    if (!(pickupDate < returnDate))
    {

        utils::printError(
            "Return date must be after pickup date.");

        return;
    }

    std::string vehicleType =
        utils::getNonEmptyString(
            "Vehicle Type (or ALL): ");

    bool found = false;

    std::cout << "\n";
    std::cout
        << "============================================================\n";

    std::cout
        << "              AVAILABLE VEHICLES\n";

    std::cout
        << "============================================================\n";

    for (const auto &vehicle : vehicles)
    {

        // Vehicle must be available
        if (vehicle.getStatus() != "AVAILABLE")
        {
            continue;
        }

        // Vehicle type filter
        if (vehicleType != "ALL" &&
            vehicle.getType() != vehicleType)
        {

            continue;
        }

        // Check date availability
        if (!isVehicleAvailable(
                vehicle.getId(),
                pickupDate,
                returnDate))
        {

            continue;
        }

        found = true;

        std::cout
            << "\nVehicle ID  : "
            << vehicle.getId();

        std::cout
            << "\nVehicle     : "
            << vehicle.getBrand()
            << " "
            << vehicle.getModel();

        std::cout
            << "\nType        : "
            << vehicle.getType();

        std::cout
            << "\nPrice/Day   : Rs. "
            << utils::formatMoney(
                   vehicle.getPricePerDay());

        std::cout
            << "\nStatus      : AVAILABLE";

        std::cout
            << "\n----------------------------------------\n";
    }

    if (found)
    {

        utils::printSuccess(
            "Vehicles are available for your selected dates.");
    }
    else
    {

        utils::printWarning(
            "No vehicles are available for these dates.");

        showAlternativeVehicles(
            pickupInput,
            returnInput,
            vehicleType);
    }
}

void RentalSystem::showAlternativeVehicles(
    const std::string &pickupDate,
    const std::string &returnDate,
    const std::string &vehicleType)
{

    Date pickup;
    Date returnDateObj;

    try
    {

        pickup = Date::parse(pickupDate);
        returnDateObj = Date::parse(returnDate);
    }
    catch (...)
    {

        return;
    }

    utils::printHeader(
        "ALTERNATIVE VEHICLES");

    bool found = false;

    for (const auto &vehicle : vehicles)
    {

        if (vehicle.getStatus() != "AVAILABLE")
        {
            continue;
        }

        if (vehicleType != "ALL" &&
            vehicle.getType() != vehicleType)
        {

            continue;
        }

        if (!isVehicleAvailable(
                vehicle.getId(),
                pickup,
                returnDateObj))
        {

            continue;
        }

        found = true;

        std::cout
            << "\nVehicle ID  : "
            << vehicle.getId();

        std::cout
            << "\nVehicle     : "
            << vehicle.getBrand()
            << " "
            << vehicle.getModel();

        std::cout
            << "\nType        : "
            << vehicle.getType();

        std::cout
            << "\nPrice/Day   : Rs. "
            << utils::formatMoney(
                   vehicle.getPricePerDay());

        std::cout
            << "\nStatus      : AVAILABLE";

        std::cout
            << "\n----------------------------------------\n";
    }

    if (!found)
    {

        utils::printInfo(
            "No alternative vehicles are available.");
    }
    else
    {

        utils::printSuccess(
            "Alternative vehicles are available.");
    }
}
