# Download external conan.cmake automatically, if it does not already exist
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES poco/1.10.1
                BUILD_TYPE "None"
                BASIC_SETUP CMAKE_TARGETS
                GENERATORS cmake_find_package cmake_paths
                OPTIONS ${CONAN_OPTIONS}
                BUILD missing)
