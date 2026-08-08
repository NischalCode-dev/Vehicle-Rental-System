#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace utils {
    int getInt(const std::string& prompt);
    double getDouble(const std::string& prompt);
    std::string getNonEmptyString(const std::string& prompt);
    std::string toLower(std::string value);
    std::string trim(const std::string& value);
    std::string formatMoney(double amount);
    std::vector<std::string> split(const std::string& text, char delimiter);
    bool isValidEmail(const std::string& email);
    bool isValidPhone(const std::string& phone);
    void printHeader(const std::string& title);
    void printFooter(const std::string& message);
    void printDivider(int width = 60);
    void printBox(const std::string& title, const std::vector<std::string>& lines);
    void printTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows);
    void printSuccess(const std::string& message);
    void printError(const std::string& message);
    void printWarning(const std::string& message);
    void printInfo(const std::string& message);
    void clearScreen();
    void pauseScreen(const std::string& message = "Press Enter to continue...");
    void printSeparator();
}

#endif
