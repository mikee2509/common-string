cmake_minimum_required(VERSION 3.7)
project(AAL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp data/StringSet.cpp data/StringSet.h generator/RandomStringGenerator.cpp generator/RandomStringGenerator.h algorithm/CommonStringFinder.cpp algorithm/CommonStringFinder.h)
add_executable(AAL ${SOURCE_FILES})