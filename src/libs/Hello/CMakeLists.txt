project(Hello LANGUAGES CXX)

# File setup
set(HEADER_FILES
  include/Hello.h
)

set(SOURCE_FILES
  src/Hello.cpp
)

# Add a library target to the project and an alias for the target name
add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_library(lib::Hello ALIAS ${PROJECT_NAME})

# Set libs solution folder
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Libs")

# Specify include directory to use when compiling
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
