#----------
# This file specifies how the project should be built, using CMake.
#----------
cmake_minimum_required(VERSION 3.14.5 FATAL_ERROR)

project(Hello-World VERSION 0.1.0 LANGUAGES CXX)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: Debug Release, MinSizeRel, RelWithDebInfo." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  message(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
endif()

# Run conan from cmake to install third party libraries
include(cmake/conan_options.cmake)
include(cmake/conan.cmake)
run_conan()

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

# Turn on using solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setup output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables."
)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single Directory for all Libraries"
)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single Directory for all static libraries."
)

# Include local project
add_subdirectory(src)
