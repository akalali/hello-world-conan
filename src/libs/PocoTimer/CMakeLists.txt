project(PocoTimer LANGUAGES CXX)

# File setup
set(HEADER_FILES
  include/PocoTimer.h
)

set(SOURCE_FILES
  src/PocoTimer.cpp
)

# Add a library target to the project and an alias for the target name
add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_library(lib::PocoTimer ALIAS ${PROJECT_NAME})

# Set libs solution folder
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Libs")

# Specify include directory to use when compiling
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Specify Poco libraries to use when linking
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    ${CONAN_LIBS}
)
