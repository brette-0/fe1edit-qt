cmake_minimum_required(VERSION 3.21)
project(fe1edit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

# Sources are globbed at configure time. CONFIGURE_DEPENDS makes CMake
# re-check the glob on every build, so new files are picked up without
# a manual re-configure.
file(GLOB FE1EDIT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

qt_add_executable(fe1edit ${FE1EDIT_SOURCES})

target_link_libraries(fe1edit PRIVATE Qt6::Widgets)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(fe1edit PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(fe1edit PRIVATE /W4)
endif()
