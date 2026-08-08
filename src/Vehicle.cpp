#include "Vehicle.h"

Vehicle::Vehicle() : id(0), vehicleNumber(""), brand(""), model(""), type(""), manufacturingYear(2000), color(""), fuelType(""), transmission(""), seatingCapacity(4), pricePerDay(0.0), mileage(0.0), status("AVAILABLE"), ratingCount(0), averageRating(0.0) {}

Vehicle::Vehicle(int id, const std::string& vehicleNumber, const std::string& brand,
                 const std::string& model, const std::string& type, int year,
                 const std::string& color, const std::string& fuelType,
                 const std::string& transmission, int seatingCapacity,
                 double pricePerDay, double mileage, const std::string& status)
    : id(id), vehicleNumber(vehicleNumber), brand(brand), model(model), type(type), manufacturingYear(year), color(color), fuelType(fuelType), transmission(transmission), seatingCapacity(seatingCapacity), pricePerDay(pricePerDay), mileage(mileage), status(status), ratingCount(0), averageRating(0.0) {}

int Vehicle::getId() const { return id; }
std::string Vehicle::getVehicleNumber() const { return vehicleNumber; }
std::string Vehicle::getBrand() const { return brand; }
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getType() const { return type; }
int Vehicle::getManufacturingYear() const { return manufacturingYear; }
std::string Vehicle::getColor() const { return color; }
std::string Vehicle::getFuelType() const { return fuelType; }
std::string Vehicle::getTransmission() const { return transmission; }
int Vehicle::getSeatingCapacity() const { return seatingCapacity; }
double Vehicle::getPricePerDay() const { return pricePerDay; }
double Vehicle::getMileage() const { return mileage; }
std::string Vehicle::getStatus() const { return status; }
int Vehicle::getRatingCount() const { return ratingCount; }
double Vehicle::getAverageRating() const { return averageRating; }

void Vehicle::setStatus(const std::string& value) { status = value; }
void Vehicle::setPricePerDay(double value) { pricePerDay = value; }
void Vehicle::addRating(int rating) {
    if (rating < 1 || rating > 5) {
        return;
    }
    ++ratingCount;
    averageRating = ((averageRating * (ratingCount - 1)) + rating) / ratingCount;
}
