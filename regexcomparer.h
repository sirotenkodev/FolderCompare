#ifndef REGEXCOMPARER_H
#define REGEXCOMPARER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <regex>

class RegexComparer
{

public:
    RegexComparer(const std::filesystem::path &folder,
                  const std::filesystem::path &regex,
                  const std::filesystem::path &save
         );

public:
    void saveRegexString(const std::filesystem::path &save);

private:
    void readFolder(const std::filesystem::path path);
    void compareFolders(const std::filesystem::path path);

private:
    std::vector<std::string> m_folder;
    std::vector<std::string> m_regsFiles;
};

#endif // REGEXCOMPARER_H
