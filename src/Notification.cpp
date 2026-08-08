#include "Notification.h"

Notification::Notification() : id(0), message(""), type("INFO"), read(false) {}

Notification::Notification(int id, const std::string& message, const std::string& type, bool read)
    : id(id), message(message), type(type), read(read) {}

int Notification::getId() const { return id; }
std::string Notification::getMessage() const { return message; }
std::string Notification::getType() const { return type; }
bool Notification::isRead() const { return read; }

void Notification::markRead() { read = true; }
