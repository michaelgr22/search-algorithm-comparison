cmake_minimum_required(VERSION 3.0)
project(MySFMLApp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Recursively find all .cpp files inside src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Add all found .cpp files to the executable
add_executable(app main.cpp ${SRC_FILES})
target_link_libraries(app PRIVATE sfml-graphics sfml-window sfml-system)
