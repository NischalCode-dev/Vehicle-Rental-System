#include "FileManager.h"

#include <fstream>
#include <sstream>

bool FileManager::ensureFile(const std::string& path) {
    std::ifstream file(path);
    if (file.good()) {
        return true;
    }
    std::ofstream out(path);
    return out.good();
}

std::vector<std::string> FileManager::readLines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    if (!file.is_open()) {
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

void FileManager::writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream file(path, std::ios::trunc);
    for (const auto& line : lines) {
        file << line << "\n";
    }
}

std::string FileManager::join(const std::vector<std::string>& parts, char delimiter) {
    std::ostringstream oss;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i) {
            oss << delimiter;
        }
        oss << parts[i];
    }
    return oss.str();
}

std::vector<std::string> FileManager::split(const std::string& line, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }
    return parts;
}
