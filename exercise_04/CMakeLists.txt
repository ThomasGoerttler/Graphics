# Define project
cmake_minimum_required(VERSION 2.8)
project(cg1_blatt4)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited Configs" FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#add_definitions("-std=c++11")
SET(CMAKE_CXX_FLAGS "-std=c++0x")

# Include helpers
include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

# Set target name
set(target cg1_blatt4)

# Include QT5 libraries
set(CMAKE_AUTOMOC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)

find_package(OpenGL REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED) 

# Define source files
set(sources
	src/main.cpp
	src/mainwindow.cpp
	src/mainwindow.h
        src/mathdefinitions.h
	src/abstractexercise.cpp
	src/abstractexercise.h
	src/abstractglexercise.cpp
        src/abstractglexercise.h
        src/box.h
        src/box.cpp
        src/exercise15.h
        src/exercise15.cpp
        src/exercise16.h
        src/exercise16.cpp
        src/exercise17.cpp
        src/exercise17.h
        src/threedobject.h
        src/threedobject.cpp
)

# Create executable
add_executable(${target} ${sources})

# Create executable
include_directories(
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${target}
    ${OPENGL_LIBRARIES}
)

qt5_use_modules(${target} OpenGL Gui Widgets)
