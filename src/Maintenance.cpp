#include "Maintenance.h"

Maintenance::Maintenance() : id(0), vehicleId(0), serviceType(""), serviceDate(), cost(0.0), description(""), nextServiceDate() {}

Maintenance::Maintenance(int id, int vehicleId, const std::string& serviceType,
                         const Date& serviceDate, double cost, const std::string& description,
                         const Date& nextServiceDate)
    : id(id), vehicleId(vehicleId), serviceType(serviceType), serviceDate(serviceDate), cost(cost), description(description), nextServiceDate(nextServiceDate) {}

int Maintenance::getId() const { return id; }
int Maintenance::getVehicleId() const { return vehicleId; }
std::string Maintenance::getServiceType() const { return serviceType; }
Date Maintenance::getServiceDate() const { return serviceDate; }
double Maintenance::getCost() const { return cost; }
std::string Maintenance::getDescription() const { return description; }
Date Maintenance::getNextServiceDate() const { return nextServiceDate; }
