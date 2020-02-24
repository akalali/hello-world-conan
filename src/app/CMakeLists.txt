#----------
# Main-Application
#----------

project(Main LANGUAGES CXX)

# Add an executable target to the project
add_executable(${PROJECT_NAME} main.cpp)

# Set application solution folder
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Application")

# Specify local libraries to use when linking
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    lib::Hello
    lib::PocoTimer
)
