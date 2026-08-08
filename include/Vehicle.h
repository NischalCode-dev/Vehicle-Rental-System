#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle();
    Vehicle(int id, const std::string& vehicleNumber, const std::string& brand,
            const std::string& model, const std::string& type, int year,
            const std::string& color, const std::string& fuelType,
            const std::string& transmission, int seatingCapacity,
            double pricePerDay, double mileage, const std::string& status);

    int getId() const;
    std::string getVehicleNumber() const;
    std::string getBrand() const;
    std::string getModel() const;
    std::string getType() const;
    int getManufacturingYear() const;
    std::string getColor() const;
    std::string getFuelType() const;
    std::string getTransmission() const;
    int getSeatingCapacity() const;
    double getPricePerDay() const;
    double getMileage() const;
    std::string getStatus() const;
    int getRatingCount() const;
    double getAverageRating() const;

    void setStatus(const std::string& status);
    void setPricePerDay(double price);
    void addRating(int rating);

private:
    int id;
    std::string vehicleNumber;
    std::string brand;
    std::string model;
    std::string type;
    int manufacturingYear;
    std::string color;
    std::string fuelType;
    std::string transmission;
    int seatingCapacity;
    double pricePerDay;
    double mileage;
    std::string status;
    int ratingCount;
    double averageRating;
};

#endif
