# Define project
cmake_minimum_required(VERSION 2.6)
project(FrameworkQt)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include helpers
#include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

# Set target name
set(target FrameworkQt)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

# Define source files
set(sources
    src/main.cpp
	src/stable.h
	src/stable.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/exercise5.cpp
    src/exercise5.h
	src/util/imageview.h
	src/util/imageview.cpp
)

# Create executable
add_executable(${target} ${sources})

qt5_use_modules(${target} Widgets)
