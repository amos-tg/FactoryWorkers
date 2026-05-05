cmake_minimum_required(VERSION 3.16)

# Project name and language
project(FactoryWorkers LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard (change to 17 or 20 if you prefer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------
# ---------- LIB

# Add lib source files
file(GLOB LIB_SOURCE "lib/src/*.cpp")

add_library(factory STATIC ${LIB_SOURCE})

target_include_directories(factory
  PUBLIC
    lib/include
)

# ----------------
# ---------- TESTS

file(GLOB LIB_TESTS "lib/tests/*.cpp")

# Add the tests program executable
add_executable(tests ${LIB_TESTS})

target_link_libraries(tests PRIVATE factory)

# -------------------------------
# ----------- MENU DRIVEN PROGRAM

file(GLOB MAIN_SOURCES "src/*.cpp")

# Add the menu driven program executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE factory) 
