#include "Review.h"

Review::Review() : id(0), customerId(0), vehicleId(0), rating(0), comment(""), reviewDate() {}

Review::Review(int id, int customerId, int vehicleId, int rating,
               const std::string& comment, const Date& reviewDate)
    : id(id), customerId(customerId), vehicleId(vehicleId), rating(rating), comment(comment), reviewDate(reviewDate) {}

int Review::getId() const { return id; }
int Review::getCustomerId() const { return customerId; }
int Review::getVehicleId() const { return vehicleId; }
int Review::getRating() const { return rating; }
std::string Review::getComment() const { return comment; }
Date Review::getReviewDate() const { return reviewDate; }
