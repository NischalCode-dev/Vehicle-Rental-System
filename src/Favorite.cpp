#include "Favorite.h"

Favorite::Favorite() : customerId(0), vehicleId(0) {}

Favorite::Favorite(int customerId, int vehicleId)
    : customerId(customerId), vehicleId(vehicleId) {}

int Favorite::getCustomerId() const { return customerId; }
int Favorite::getVehicleId() const { return vehicleId; }
