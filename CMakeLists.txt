cmake_minimum_required(VERSION 3.10)
project(lab_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)

add_executable(main main.cpp)

target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/my_types
    ${CMAKE_SOURCE_DIR}/exceptions
    ${CMAKE_SOURCE_DIR}/data_org
    ${CMAKE_SOURCE_DIR}/sequence
    ${CMAKE_SOURCE_DIR}/ADT
    ${CMAKE_SOURCE_DIR}/UI
)