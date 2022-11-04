cmake_minimum_required(VERSION 3.16)
project(libhttp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.cmake")
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_VERSION "0.0.1")

include(DebPack)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_library(libhttp ${SOURCES})

target_link_libraries(libhttp
        spdlog::spdlog
        fmt::fmt
        )

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    deb_dependence(DIRECTORY "${PROJECT_SOURCE_DIR}/include/libhttp" TYPE INCLUDE TARGET ${PROJECT_NAME})
    deb_dependence(FILE "${PROJECT_SOURCE_DIR}/include/libhttp.hpp" TYPE INCLUDE TARGET ${PROJECT_NAME})
    add_definitions(-O2)
    build_deb(
            TARGET ${PROJECT_NAME}
            NAME ${PROJECT_NAME}-dev
            VERSION ${PROJECT_VERSION}
            SUMMARY "small fast http library on C++"
            VENDOR "Pockusaev Andrey"
            MAINTAINER "Pockusaev Andrey"
            CONTACT "a.pokusaev@etd-online.ru"
            LIB_DEPENDS "libspdlog-dev" "libfmt-dev"
    )
endif ()