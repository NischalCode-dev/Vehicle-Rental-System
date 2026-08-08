#include "Payment.h"

Payment::Payment() : id(0), bookingId(0), customerId(0), amount(0.0), method("Cash"), paymentDate(""), transactionId(""), status("PENDING") {}

Payment::Payment(int id, int bookingId, int customerId, double amount,
                 const std::string& method, const std::string& paymentDate,
                 const std::string& transactionId, const std::string& status)
    : id(id), bookingId(bookingId), customerId(customerId), amount(amount), method(method), paymentDate(paymentDate), transactionId(transactionId), status(status) {}

int Payment::getId() const { return id; }
int Payment::getBookingId() const { return bookingId; }
int Payment::getCustomerId() const { return customerId; }
double Payment::getAmount() const { return amount; }
std::string Payment::getMethod() const { return method; }
std::string Payment::getPaymentDate() const { return paymentDate; }
std::string Payment::getTransactionId() const { return transactionId; }
std::string Payment::getStatus() const { return status; }
