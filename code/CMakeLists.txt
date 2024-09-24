cmake_minimum_required(VERSION 3.13)
project(PCO_LAB02)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Core Gui Concurrent Widgets REQUIRED)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE FORMS "ui/*.ui")

add_executable(pco_bogosort ${SOURCES} ${HEADERS} ${FORMS})
target_link_libraries(pco_bogosort PRIVATE Qt5::Core Qt5::Gui Qt5::Concurrent Qt5::Widgets -lpcosynchro)
