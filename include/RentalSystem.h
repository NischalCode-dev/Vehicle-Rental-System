#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <string>
#include <vector>
#include "Admin.h"
#include "Booking.h"
#include "Coupon.h"
#include "Customer.h"
#include "Favorite.h"
#include "Invoice.h"
#include "Maintenance.h"
#include "Notification.h"
#include "Payment.h"
#include "Report.h"
#include "Review.h"
#include "User.h"
#include "Vehicle.h"

class RentalSystem {
public:
    RentalSystem();
    void run();

private:
    void initializeDataFiles();
    void showMainMenu();
    void showAdminMenu();
    void showCustomerMenu();
    void registerCustomer();
    void loginUser();
    void loadUsers();
    void saveUsers();
    void loadVehicles();
    void saveVehicles();
    void loadBookings();
    void saveBookings();
    void loadPayments();
    void savePayments();
    void loadMaintenance();
    void saveMaintenance();
    void loadReviews();
    void saveReviews();
    void addVehicle();
    void viewVehicles();
    void browseVehicles();
    void seedSampleData();
    void displayAbout();
    void createBooking();
    void viewBookings();
    
    void cancelBooking();

bool isVehicleAvailable(
    int vehicleId,
    const Date& pickupDate,
    const Date& returnDate
) const;

void smartVehicleAvailability();

void showAlternativeVehicles(
    const std::string& pickupDate,
    const std::string& returnDate,
    const std::string& vehicleType
);
    void processPickup();
    void processReturn();
    void makePayment();
    void generateInvoice(const Booking& booking, const Payment& payment);
    void viewInvoice();
    void addMaintenance();
    void viewMaintenance();
    void addReview();
    void showReports();
    void showAdminDashboard();
    void showCustomerDashboard();
    void loadCoupons();
    void saveCoupons();
    void loadNotifications();
    void saveNotifications();
    void loadFavorites();
    void saveFavorites();
    void addCoupon();
    void viewCoupons();
    void manageCoupons();
    void viewNotifications();
    void markNotificationRead();
    void addNotification(const std::string& message, const std::string& type);
    void showCouponMenu();
    void addFavorite();
    void removeFavorite();
    void viewFavorites();
    void manageFavorites();
    void manageNotifications();
    void showRecommendations();
    bool isFavorite(int vehicleId) const;
    bool isUsernameTaken(const std::string& username) const;
    bool authenticate(const std::string& username, const std::string& password, std::string& role) const;
    std::vector<User> users;
    std::vector<Vehicle> vehicles;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;
    std::vector<Maintenance> maintenanceRecords;
    std::vector<Review> reviews;
    std::vector<Coupon> coupons;
    std::vector<Notification> notifications;
    std::vector<Favorite> favorites;
    User* currentUser;
    bool loggedIn;
    int nextUserId;
    int nextVehicleId;
    int nextBookingId;
    int nextPaymentId;
    int nextMaintenanceId;
    int nextReviewId;
};

#endif
