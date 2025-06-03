#include "regexcomparer.h"

///////////////////////////////////////////////////////////////////////////////
namespace fs = std::filesystem;

RegexComparer::RegexComparer(
        const std::filesystem::path &folder,
        const std::filesystem::path &regex,
        const std::filesystem::path &save)
{
    if (!fs::exists(folder)) {
        std::cerr << "folder is not exist." << std::endl;
    } else {
        readFolder(folder);
        compareFolders(regex);
    }

    saveRegexString(save);
}

void RegexComparer::saveRegexString(const std::filesystem::path &save)
{
    std::ofstream file(save);
    if(m_regsFiles.empty()) {
        std::cerr << "All files equal" << "\n";
    } else {
        for(const auto &f : m_regsFiles) {
            file << f << std::endl;
        }
    }
}

void RegexComparer::readFolder(const std::filesystem::path path)
{
    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.status())) {
                m_folder.push_back(fs::absolute(entry.path()).string());
            } else if (fs::is_directory(entry.status())) {
                readFolder(entry.path());
            }
        }
    } else {
        std::cerr << "Cant open folder: " << path << "\n";
    }
}

void RegexComparer::compareFolders(const std::filesystem::path path)
{
    std::ifstream file(path);
    if(file.is_open()) {
        std::string load;
        while(std::getline(file, load)) {
            std::regex pattern{load};
            std::smatch match;
            for(const auto &f : m_folder) {
                if(!std::regex_search(f, match, pattern)) {
                    continue;
                }

                m_regsFiles.push_back(f);
            }
        }
    } else {
        std::cerr << "Error while open files: " << path << "\n";
    }

}
