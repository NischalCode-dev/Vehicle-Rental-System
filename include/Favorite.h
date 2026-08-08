#ifndef FAVORITE_H
#define FAVORITE_H

#include <string>

class Favorite {
public:
    Favorite();
    Favorite(int customerId, int vehicleId);

    int getCustomerId() const;
    int getVehicleId() const;

private:
    int customerId;
    int vehicleId;
};

#endif
