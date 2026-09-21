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

# 6. Define source files
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

# 9. Link raylib + platform-specific libraries
if(EMSCRIPTEN)
    # Web build: output index.html / index.js / index.wasm
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "index"
        SUFFIX ".html"
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        "-sUSE_GLFW=3"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASSERTIONS=0"
        "--shell-file" "${raylib_SOURCE_DIR}/src/minshell.html"
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        raylib
        m           # Math library
        dl          # Dynamic linking
        pthread     # POSIX threads
        X11         # X11 for Linux
    )
endif()

# 10. Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# 11. Print confirmation
message(STATUS "=========================================")
message(STATUS "Building ${PROJECT_NAME}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Sources: ${SOURCES}")
message(STATUS "Output: ${CMAKE_BINARY_DIR}")
message(STATUS "=========================================")