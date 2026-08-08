#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
public:
    Notification();
    Notification(int id, const std::string& message, const std::string& type, bool read);

    int getId() const;
    std::string getMessage() const;
    std::string getType() const;
    bool isRead() const;

    void markRead();

private:
    int id;
    std::string message;
    std::string type;
    bool read;
};

#endif
