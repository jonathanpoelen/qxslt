cmake_minimum_required(VERSION 2.8.8)
project(qxslt)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5XmlPatterns REQUIRED)

include(CMakeDefinitions.txt)

set(qxslt_SRCS qxslt.cpp)

add_executable(qxslt ${qxslt_SRCS})

qt5_use_modules(qxslt XmlPatterns)
