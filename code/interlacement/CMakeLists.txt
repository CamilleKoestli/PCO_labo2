cmake_minimum_required(VERSION 3.0)
project(interlacement)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(PCO_lab01_interlacement ${SOURCES})

target_link_libraries(PCO_lab01_interlacement PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test -lpcosynchro -lgtest -lpthread)
