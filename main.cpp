#include <string>

#include <cxxopts.hpp>

#include "comparer.h"
#include "regexcomparer.h"

int main(int argc, char* argv[])
{
    cxxopts::Options options(argv[0], "File comparer");
    options.add_options()
            ("f,first", "First folder", cxxopts::value<std::string>()->default_value("f1"))
            ("s,second", "Second folder", cxxopts::value<std::string>()->default_value("regex.txt"))
            ("t,third", "Third file", cxxopts::value<std::string>()->default_value("saveregdiff.txt"));

    const auto result = options.parse(argc, argv);

//    Comparer c(result["first"].as<std::string>(),
//                result["second"].as<std::string>(),
//                result["third"].as<std::string>());

    RegexComparer c(result["first"].as<std::string>(),
                result["second"].as<std::string>(),
                result["third"].as<std::string>());


    return 0;
}
