#include "Utils.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

namespace utils {
    namespace {
        void ensureConsoleEncoding() {
#ifdef _WIN32
            static bool initialized = false;
            if (!initialized) {
                SetConsoleOutputCP(CP_UTF8);
                SetConsoleCP(CP_UTF8);
                initialized = true;
            }
#endif
        }

        std::string repeat(const std::string& text, int count) {
            std::string result;
            result.reserve(text.size() * count);
            for (int i = 0; i < count; ++i) {
                result += text;
            }
            return result;
        }
    }

    std::string trim(const std::string& value) {
        const auto begin = value.find_first_not_of(" \t\r\n");
        if (begin == std::string::npos) {
            return "";
        }
        const auto end = value.find_last_not_of(" \t\r\n");
        return value.substr(begin, end - begin + 1);
    }

    std::string toLower(std::string value) {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return value;
    }

    std::string getNonEmptyString(const std::string& prompt) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            input = trim(input);
            if (!input.empty()) {
                return input;
            }
            printError("Value cannot be empty.");
        }
    }

    int getInt(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string line;
            std::getline(std::cin, line);
            try {
                size_t pos = 0;
                int value = std::stoi(line, &pos);
                if (pos != line.size()) {
                    throw std::invalid_argument("extra characters");
                }
                return value;
            } catch (const std::exception&) {
                printError("Please enter a valid integer.");
            }
        }
    }

    double getDouble(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string line;
            std::getline(std::cin, line);
            try {
                size_t pos = 0;
                double value = std::stod(line, &pos);
                if (pos != line.size()) {
                    throw std::invalid_argument("extra characters");
                }
                return value;
            } catch (const std::exception&) {
                printError("Please enter a valid number.");
            }
        }
    }

    std::string formatMoney(double amount) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << amount;
        return oss.str();
    }

    std::vector<std::string> split(const std::string& text, char delimiter) {
        std::vector<std::string> parts;
        std::stringstream stream(text);
        std::string item;
        while (std::getline(stream, item, delimiter)) {
            parts.push_back(item);
        }
        return parts;
    }

    bool isValidEmail(const std::string& email) {
        const auto at = email.find('@');
        const auto dot = email.find_last_of('.');
        return at != std::string::npos && dot != std::string::npos && at < dot;
    }

    bool isValidPhone(const std::string& phone) {
        if (phone.size() < 7) {
            return false;
        }
        for (char ch : phone) {
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                return false;
            }
        }
        return true;
    }

    void printHeader(const std::string& title) {
        ensureConsoleEncoding();
        int width = std::max(20, static_cast<int>(title.size() + 4));
        std::cout << "\n+" << repeat("-", width) << "+\n";
        std::cout << "| " << std::left << std::setw(width - 2) << title << "|\n";
        std::cout << "+" << repeat("-", width) << "+\n";
    }

    void printFooter(const std::string& message) {
        ensureConsoleEncoding();
        std::cout << "\n+ " << message << " +\n";
    }

    void printDivider(int width) {
        ensureConsoleEncoding();
        std::cout << repeat("-", width) << "\n";
    }

    void printBox(const std::string& title, const std::vector<std::string>& lines) {
        ensureConsoleEncoding();
        int width = 60;
        if (title.size() + 6 > static_cast<size_t>(width)) {
            width = static_cast<int>(title.size() + 8);
        }
        std::cout << "+" << repeat("-", width) << "+\n";
        std::cout << "| " << std::left << std::setw(width - 2) << title << "|\n";
        std::cout << "+" << repeat("-", width) << "+\n";
        for (const std::string& line : lines) {
            std::cout << "| " << std::left << std::setw(width - 2) << line << "|\n";
        }
        std::cout << "+" << repeat("-", width) << "+\n";
    }

    void printTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows) {
        ensureConsoleEncoding();
        if (headers.empty()) {
            return;
        }

        std::vector<size_t> widths(headers.size(), 0);
        for (size_t i = 0; i < headers.size(); ++i) {
            widths[i] = headers[i].size();
        }

        for (const auto& row : rows) {
            for (size_t i = 0; i < headers.size() && i < row.size(); ++i) {
                widths[i] = std::max(widths[i], row[i].size());
            }
        }

        auto printRow = [&](const std::vector<std::string>& values) {
            std::cout << "│ ";
            for (size_t i = 0; i < headers.size() && i < values.size(); ++i) {
                std::cout << std::left << std::setw(static_cast<int>(widths[i])) << values[i] << " │ ";
            }
            std::cout << "\n";
        };

        std::cout << "+";
        for (size_t i = 0; i < widths.size(); ++i) {
            std::cout << repeat("-", static_cast<int>(widths[i] + 2));
            if (i + 1 < widths.size()) {
                std::cout << "+";
            }
        }
        std::cout << "+\n";

        printRow(headers);

        std::cout << "+";
        for (size_t i = 0; i < widths.size(); ++i) {
            std::cout << repeat("-", static_cast<int>(widths[i] + 2));
            if (i + 1 < widths.size()) {
                std::cout << "+";
            }
        }
        std::cout << "+\n";

        for (const auto& row : rows) {
            printRow(row);
        }

        std::cout << "+";
        for (size_t i = 0; i < widths.size(); ++i) {
            std::cout << repeat("-", static_cast<int>(widths[i] + 2));
            if (i + 1 < widths.size()) {
                std::cout << "+";
            }
        }
        std::cout << "+\n";
    }

    void printSuccess(const std::string& message) {
        ensureConsoleEncoding();
        std::cout<< message << "\n";
    }

    void printError(const std::string& message) {
        ensureConsoleEncoding();
        std::cout<< message << "\n";
    }

    void printWarning(const std::string& message) {
        ensureConsoleEncoding();
        std::cout<< message << "\n";
    }

    void printInfo(const std::string& message) {
        ensureConsoleEncoding();
        std::cout<< message << "\n";
    }

    void clearScreen() {
        ensureConsoleEncoding();
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void pauseScreen(const std::string& message) {
        ensureConsoleEncoding();
        std::cout << "\n" << message << " ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void printSeparator() {
        ensureConsoleEncoding();
        std::cout << "----------------------------------------\n";
    }
}
