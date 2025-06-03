#ifndef COMPARER_H
#define COMPARER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>


#include "filestruct.h"
namespace fs = std::experimental::filesystem;
class Comparer
{
    enum Folders {
        FOLDER1,
        FOLDER2
    };

public:
    Comparer(const std::filesystem::path &folder1,
             const std::filesystem::path &folder2,
             const std::filesystem::path &save
    );

public:
    void saveDifferent(const std::filesystem::path &save);

private:
    void readFile(Folders f, const std::filesystem::path path);
    void readFolder(Folders folder, const std::filesystem::path path);
    void compareFolders();

private:
    std::filesystem::path m_folder1Path;
    std::filesystem::path m_folder2Path;
    std::vector<File> m_folder1;
    std::vector<File> m_folder2;
    std::vector<File> m_diffFiles;

};

#endif // COMPARER_H
