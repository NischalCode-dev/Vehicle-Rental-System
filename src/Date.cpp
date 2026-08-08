#include "Date.h"

#include <sstream>
#include <stdexcept>
#include <vector>

Date::Date() : dayValue(1), monthValue(1), yearValue(2000) {}

Date::Date(int day, int month, int year) : dayValue(day), monthValue(month), yearValue(year) {}

bool Date::isLeapYear() const {
    if (yearValue % 400 == 0) {
        return true;
    }
    if (yearValue % 100 == 0) {
        return false;
    }
    return yearValue % 4 == 0;
}

bool Date::isValid() const {
    if (yearValue < 1900 || monthValue < 1 || monthValue > 12 || dayValue < 1) {
        return false;
    }

    static const std::vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[monthValue - 1];
    if (monthValue == 2 && isLeapYear()) {
        maxDay = 29;
    }
    return dayValue <= maxDay;
}

int Date::day() const {
    return dayValue;
}

int Date::month() const {
    return monthValue;
}

int Date::year() const {
    return yearValue;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << (dayValue < 10 ? "0" : "") << dayValue << "-"
        << (monthValue < 10 ? "0" : "") << monthValue << "-" << yearValue;
    return oss.str();
}

Date Date::parse(const std::string& value) {
    std::stringstream ss(value);
    std::string token;
    std::vector<int> parts;
    while (std::getline(ss, token, '-')) {
        parts.push_back(std::stoi(token));
    }
    if (parts.size() != 3) {
        throw std::invalid_argument("Invalid date format");
    }
    Date result(parts[0], parts[1], parts[2]);
    if (!result.isValid()) {
        throw std::invalid_argument("Invalid date");
    }
    return result;
}

int Date::daysBetween(const Date& start, const Date& end) {
    if (end < start) {
        return 0;
    }

    const int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    Date current = start;

    while (!(current == end)) {
        int year = current.year();
        int month = current.month();
        int day = current.day();
        if (month == 12 && day == 31) {
            current = Date(1, 1, year + 1);
        } else if (day == daysPerMonth[month - 1] || (month == 2 && current.isLeapYear() && day == 29)) {
            current = Date(1, month + 1, year);
        } else {
            current = Date(day + 1, month, year);
        }
        ++days;
    }
    return days + 1;
}

bool Date::operator<(const Date& other) const {
    if (yearValue != other.yearValue) {
        return yearValue < other.yearValue;
    }
    if (monthValue != other.monthValue) {
        return monthValue < other.monthValue;
    }
    return dayValue < other.dayValue;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator==(const Date& other) const {
    return dayValue == other.dayValue && monthValue == other.monthValue && yearValue == other.yearValue;
}
