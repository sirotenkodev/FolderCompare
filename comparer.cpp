#include <functional>

#include "comparer.h"

///////////////////////////////////////////////////////////////////////////////
namespace fs = std::filesystem;

Comparer::Comparer(const fs::path &folder1, const fs::path &folder2, const fs::path &save)
    : m_folder1Path{folder1}
    , m_folder2Path{folder2}
{
    if (!fs::exists(folder1) || !fs::exists(folder2)) {
        std::cerr << "No one folder is exist." << std::endl;
    } else {
        readFolder(FOLDER1,folder1);
        readFolder(FOLDER2,folder2);
        compareFolders();
    }

    saveDifferent(save);
}

void Comparer::saveDifferent(const std::filesystem::path &save)
{
    std::ofstream file(save);
    if(m_diffFiles.empty()) {
        std::cerr << "All files equal" << "\n";
    } else {
        for(const auto &f : m_diffFiles) {
            file << f.path << std::endl;
        }
    }
}

void Comparer::readFile(Folders folder, const std::filesystem::path path)
{
    std::ifstream file(path);
    if(file.is_open()) {
        File f;
        f.path = path;
        std::string load;
        while(std::getline(file, load)) {
            f.text += load;
        }
        std::hash<std::string> hash_fn;
        f.crc = hash_fn(f.text);
        switch (folder) {
        case Comparer::FOLDER1:
            m_folder1.push_back(f);
            break;
        case Comparer::FOLDER2:
            m_folder2.push_back(f);
            break;

        }
    }  else {
        std::cerr << "Error while open files: " << path << "\n";
    }
}


void Comparer::readFolder(Folders folder, const std::filesystem::path path)
{
    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            if(fs::is_regular_file(entry.status())) {
                readFile(folder, entry.path());
            } else if(fs::is_directory(entry.status())) {
                readFolder(folder, entry.path());
            }
        }
    } else {
        std::cerr << "Cant open folder: " << path << "\n";
    }
}

void Comparer::compareFolders()
{
    for(const auto &f : m_folder2) {
        auto current = fs::absolute(m_folder1Path);
        current += fs::path::preferred_separator;
        current += f.path.filename();
        if(!fs::exists(current)) {
            m_diffFiles.push_back(f);
        } else {
            for(const auto &f1 : m_folder1) {
                if(f1.path.filename().compare(f.path.filename()) == 0) {
                    if(f1.crc != f.crc) {
                        m_diffFiles.push_back(f);
                    }
                }
            }
        }
    }
}

