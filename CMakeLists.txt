# 1. Project definition
cmake_minimum_required(VERSION 3.14)
project(RaylibProject VERSION 0.1 LANGUAGES CXX)

# 2. C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Include FetchContent
include(FetchContent)

# 4. Declare raylib dependency
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
    GIT_SHALLOW TRUE
)

# 5. Fetch raylib
FetchContent_MakeAvailable(raylib)

# 6. Define source files (EXPLICITLY)
file(GLOB_RECURSE SOURCES 
    CONFIGURE_DEPENDS  # This makes CMake rescan when files change
    "src/*.cpp"
)
message(STATUS "Found source files: ${SOURCES}")

# 7. Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 8. Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 9. Link raylib and Linux system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib
    m           # Math library
    dl          # Dynamic linking
    pthread     # POSIX threads
    X11         # X11 for Linux
)

# 10. Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# 11. Print confirmation
message(STATUS "=========================================")
message(STATUS "Building ${PROJECT_NAME} on Linux")
message(STATUS "Sources: ${SOURCES}")
message(STATUS "Output: ${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
message(STATUS "=========================================")