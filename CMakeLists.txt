cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "export the build rules into a JSON files for clang-tidy" FORCE)

project("tetris")

#Include paths to specify under windows
set(SDL2_PATH "C:/dev/libs/SDL2-2.0.9")
set(SDL2_IMAGE_PATH "C:/dev/libs/SDL2_image-2.0.4")
set(SDL2_TTF_PATH "C:/dev/libs/SDL2_ttf-2.0.14")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(includes
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

file(GLOB_RECURSE HEADER_FILES "includes/*.h")
file(GLOB_RECURSE SOURCE_FILES "sources/*.cpp")

#Hide console when built with visual studio
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} includes/menu_command.h includes/menu_command.h includes/menu_command.h includes/menu_commands.h sources/menu_options.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
                                      ${SDL2_IMAGE_LIBRARIES}
                                      ${SDL2_TTF_LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -Wunused-parameter -Wextra -Wall)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PUBLIC -O0)
else ()
    target_compile_options(${PROJECT_NAME} PUBLIC -O3)
endif ()

add_subdirectory(./test)