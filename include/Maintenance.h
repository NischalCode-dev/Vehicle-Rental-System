#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>
#include "Date.h"

class Maintenance {
public:
    Maintenance();
    Maintenance(int id, int vehicleId, const std::string& serviceType,
                const Date& serviceDate, double cost, const std::string& description,
                const Date& nextServiceDate);

    int getId() const;
    int getVehicleId() const;
    std::string getServiceType() const;
    Date getServiceDate() const;
    double getCost() const;
    std::string getDescription() const;
    Date getNextServiceDate() const;

private:
    int id;
    int vehicleId;
    std::string serviceType;
    Date serviceDate;
    double cost;
    std::string description;
    Date nextServiceDate;
};

#endif
