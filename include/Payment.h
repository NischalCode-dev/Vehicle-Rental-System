#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class Payment {
public:
    Payment();
    Payment(int id, int bookingId, int customerId, double amount,
            const std::string& method, const std::string& paymentDate,
            const std::string& transactionId, const std::string& status);

    int getId() const;
    int getBookingId() const;
    int getCustomerId() const;
    double getAmount() const;
    std::string getMethod() const;
    std::string getPaymentDate() const;
    std::string getTransactionId() const;
    std::string getStatus() const;

private:
    int id;
    int bookingId;
    int customerId;
    double amount;
    std::string method;
    std::string paymentDate;
    std::string transactionId;
    std::string status;
};

#endif
