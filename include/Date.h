#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    Date();
    Date(int day, int month, int year);

    bool isValid() const;
    bool isLeapYear() const;
    int day() const;
    int month() const;
    int year() const;

    std::string toString() const;
    static Date parse(const std::string& value);
    static int daysBetween(const Date& start, const Date& end);
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator==(const Date& other) const;

private:
    int dayValue;
    int monthValue;
    int yearValue;
};

#endif
