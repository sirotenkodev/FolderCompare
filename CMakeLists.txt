cmake_minimum_required(VERSION 3.14)

project(FolderCompare LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts
    GIT_TAG        master
)

FetchContent_MakeAvailable(cxxopts)

add_executable(FolderCompare main.cpp comparer.h comparer.cpp regexcomparer.h regexcomparer.cpp filestruct.h)

target_link_libraries(FolderCompare PRIVATE cxxopts -lc++fs)
