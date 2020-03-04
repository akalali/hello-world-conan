#----------
# This file specifies how the project should be built, using CMake.
#----------
cmake_minimum_required(VERSION 3.14.5 FATAL_ERROR)

project(Hello-World VERSION 0.1.0 LANGUAGES CXX)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug, Release, MinSizeRel, RelWithDebInfo." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  message(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
endif()

set(CONAN_CMAKE FALSE CACHE BOOL
    "Enable to download third party dependencies withing CMake. Disable to install them with Conan separately.")
set(CONAN_CMD "" CACHE FILEPATH
    "File-path to the Conan executable")

if(CONAN_CMAKE)
  # Run Conan from CMake to install third party libraries
  message(STATUS "Install libraries using CMake")
  include(cmake/conan_options.cmake)
  include(cmake/conan_run.cmake)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/conan_paths.cmake)
  # Either conan_paths.cmake exists because of a separate 'conan install' using the conanfile.txt
  # or it has been created via this CMakeLists.txt.
  include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
else()
  message(FATAL_ERROR "Requirements not installed\n"
                      "Please install requirements using 'conan install' "
                      "or enable CONAN_CMAKE and set the path to the Conan executable with CONAN_CMD.")
endif()

# Turn on using solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setup output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all executables.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single Directory for all libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single Directory for all static libraries.")

# Include local project
add_subdirectory(src)
