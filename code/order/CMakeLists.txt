cmake_minimum_required(VERSION 3.0)
project(order)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(PCO_lab01_order ${SOURCES})

target_link_libraries(PCO_lab01_order PRIVATE -lpcosynchro -lgtest -lpthread)
