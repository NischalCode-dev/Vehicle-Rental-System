#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class FileManager {
public:
    static bool ensureFile(const std::string& path);
    static std::vector<std::string> readLines(const std::string& path);
    static void writeLines(const std::string& path, const std::vector<std::string>& lines);
    static std::string join(const std::vector<std::string>& parts, char delimiter);
    static std::vector<std::string> split(const std::string& line, char delimiter);
};

#endif
