cmake_minimum_required(VERSION 4.1)
project(fraycast VERSION 0.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

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

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.10
)
FetchContent_MakeAvailable(SDL3)

# FrayCast
set(FRAYCAST_HEADERS

        include/fraycast/global/global.hpp
        include/fraycast/util/argparse/argparse.hpp

        include/tengine/util/logger/filter.hpp
        include/tengine/util/logger/i_logsink.hpp
        include/tengine/util/logger/logger.hpp
        include/tengine/util/logger/logger_macros.hpp
        include/tengine/util/logger/log_level.hpp
        include/tengine/util/logger/sinks/file_sink.hpp
        include/tengine/util/logger/sinks/terminal_sink.hpp
        include/tengine/util/cfgparse/cfg_node.hpp
        include/tengine/util/cfgparse/parser.hpp
        include/tengine/util/cfgparse/serializer.hpp
        include/tengine/util/filesystem/recur_file_by_ext.hpp

)
set(FRAYCAST_SOURCES

        src/fraycast/main.cpp

        src/tengine/util/logger/logger.cpp
        src/tengine/util/logger/sinks/terminal_sink.cpp
        src/tengine/util/logger/sinks/file_sink.cpp
        src/tengine/util/cfgparse/parser.cpp
        src/tengine/util/cfgparse/serializer.cpp

)

add_executable(fraycast ${FRAYCAST_SOURCES} ${FRAYCAST_HEADERS})
target_link_libraries(fraycast PUBLIC fmt::fmt)
target_link_libraries(fraycast PUBLIC SDL3::SDL3)

target_include_directories(fraycast
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include>
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/fraycast-assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")