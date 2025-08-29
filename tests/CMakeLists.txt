add_executable(tests_runner tests_runner.cpp)

target_include_directories(tests_runner PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data_org
    ${CMAKE_CURRENT_SOURCE_DIR}/sequence
    ${CMAKE_CURRENT_SOURCE_DIR}/ADT
    ${CMAKE_SOURCE_DIR}/my_types
    ${CMAKE_SOURCE_DIR}/doctest
    ${CMAKE_SOURCE_DIR}/exceptions
    ${CMAKE_SOURCE_DIR}/data_org
    ${CMAKE_SOURCE_DIR}/sequence
    ${CMAKE_SOURCE_DIR}/ADT
)