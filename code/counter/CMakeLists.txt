cmake_minimum_required(VERSION 3.0)
project(counter)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
endif()

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mythread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/dialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mythread.h
)

set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/dialog.ui
)

# qt5_wrap_ui(UI_HEADERS ${FORMS})

add_executable(PCO_lab01_counter ${SOURCES} ${HEADERS} ${FORMS})

if (Qt5_FOUND)
    target_link_libraries(PCO_lab01_counter PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets -lpcosynchro)
else ()
    target_link_libraries(PCO_lab01_counter PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets -lpcosynchro)
endif()
