cmake_minimum_required(VERSION 2.8)

set(SDL2_PATH "C:/cpp_tools/SDL2-2.0.5/i686-w64-mingw32")

project("tetris")

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

include_directories(includes
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

file(GLOB_RECURSE HEADER_FILES "includes/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(Tutorial ${SOURCE_FILES} ${HEADER_FILES} includes/game.h src/game.cpp)

target_link_libraries(Tutorial ${SDL2_LIBRARY})
