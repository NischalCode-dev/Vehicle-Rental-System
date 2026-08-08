#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include "Date.h"

class Review {
public:
    Review();
    Review(int id, int customerId, int vehicleId, int rating,
           const std::string& comment, const Date& reviewDate);

    int getId() const;
    int getCustomerId() const;
    int getVehicleId() const;
    int getRating() const;
    std::string getComment() const;
    Date getReviewDate() const;

private:
    int id;
    int customerId;
    int vehicleId;
    int rating;
    std::string comment;
    Date reviewDate;
};

#endif
