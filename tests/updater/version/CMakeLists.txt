cmake_minimum_required(VERSION 3.16)
project(tests_updater_version VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS})
set(CMAKE_AUTORCC ON)

enable_testing(true)

# ===========================Including Project Files===========================
file(GLOB_RECURSE SOURCES
    ../../../src/updater/version.cpp
    ../../../src/updater/version.h
        test_updater_version.cpp
)
add_definitions(-DQT_NO_DEBUG_OUTPUT)

qt_add_executable(${PROJECT_NAME} ${SOURCES})
add_test(NAME ${PROJECT_NAME} COMMAND "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Test
)