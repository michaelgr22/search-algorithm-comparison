cmake_minimum_required(VERSION 3.10)
project(MySFMLApp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Recursively find all .cpp files inside src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Shared source files
set(SOURCES main.cpp ${SRC_FILES})

# Normal build (no sanitizers)
add_executable(app ${SOURCES})
target_link_libraries(app PRIVATE sfml-graphics sfml-window sfml-system)

# ASan build
add_executable(app_asan ${SOURCES})
target_compile_options(app_asan PRIVATE -fsanitize=address -g -O1)
target_link_options(app_asan PRIVATE -fsanitize=address)
target_link_libraries(app_asan PRIVATE sfml-graphics sfml-window sfml-system)
