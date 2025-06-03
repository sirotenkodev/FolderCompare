#ifndef FILESTRUCT_H
#define FILESTRUCT_H

#include <filesystem>
#include <string>

struct File {
    std::filesystem::path path;
    std::string text;
    size_t crc;
};

#endif // FILESTRUCT_H
