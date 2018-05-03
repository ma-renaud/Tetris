cmake_minimum_required(VERSION 2.8)

project("tetris")

set(SDL2_PATH "C:/cpp_tools/SDL2-2.0.5/i686-w64-mingw32")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(includes
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB_RECURSE HEADER_FILES "includes/*.h")
file(GLOB_RECURSE SOURCE_FILES "sources/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
                                      ${SDL2_IMAGE_LIBRARIES})

add_subdirectory(./test)
