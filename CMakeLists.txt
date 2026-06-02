cmake_minimum_required(VERSION 4.1)
project(fraycast VERSION 0.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Build metadata
set(FRAYCAST_BUILD_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
set(FRAYCAST_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
set(FRAYCAST_BUILD_PLATFORM "${CMAKE_SYSTEM}")
string(TIMESTAMP FRAYCAST_BUILD_TIME "%Y-%m-%d %H:%M")
set(FRAYCAST_BUILD_NOTES "Build notes not specified." CACHE STRING "Custom notes for this build of fraycast.")

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/fraycast/fraycast_build_details.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/fraycast/fraycast_build_details.hpp
)

# Dependencies
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.1.0)
FetchContent_MakeAvailable(fmt)

# PWC
set(FRAYCAST_HEADERS)
set(FRAYCAST_SOURCES

        src/main.cpp

)

add_executable(fraycast ${FRAYCAST_SOURCES} ${FRAYCAST_HEADERS})
target_link_libraries(fraycast PUBLIC fmt::fmt)

target_include_directories(fraycast
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include>
)