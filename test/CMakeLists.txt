project(tetris C CXX)
cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 14)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
        # Disable install step
        INSTALL_COMMAND ""
        BUILD_BYPRODUCTS ${binary_dir}/lib/gtestd.lib
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by matrix programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gtestd.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
ELSE()
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
ENDIF()

# Create a libgmock target to be used as a dependency by matrix programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gmockd.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
ELSE()
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
ENDIF()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
        "${source_dir}/googlemock/include"
        "../include")

message(STATUS "${source_dir}")
message(STATUS "${binary_dir}")

include_directories("includes")
include_directories("../includes")

file(GLOB HEADER_FILES "../includes/*.h")
file(GLOB_RECURSE SOURCE_FILES "sources/*.cpp"
                               "../sources/well.cpp"
                               "../sources/bag.cpp")
IF(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /Z7 /Od")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd /Z7 /Od")
ENDIF()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(TestingWithGTest ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(TestingWithGTest Threads::Threads libgtest libgmock)