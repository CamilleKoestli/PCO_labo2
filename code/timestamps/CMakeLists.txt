cmake_minimum_required(VERSION 3.0)
project(timestamps)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(PCO_lab01_timestamps ${SOURCES})

target_link_libraries(PCO_lab01_timestamps PRIVATE -lpcosynchro -lgtest -lpthread)

add_custom_target(copy_script ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/show_graphic_from_exec.py
    ${CMAKE_CURRENT_BINARY_DIR}/show_graphic_from_exec.py
    COMMENT "Copying python script to build directory"
    VERBATIM
)

add_dependencies(PCO_lab01_timestamps copy_script)

