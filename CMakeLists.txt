cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(intfl)


add_executable(intfl src/main.cpp)

target_sources(intfl
    PRIVATE
    src/Directory.cpp
    src/File.cpp
    src/Commands.cpp
    src/HandleInput.cpp
    src/App.cpp
    src/PrintFileRepr.cpp
)

target_include_directories(
    intfl PRIVATE "include"
)

set(CLI11_PRECOMPILED ON)
add_subdirectory(external/CLI11)

target_link_libraries(intfl PRIVATE CLI11::CLI11)

option(USE_N_CURSES "Enable ncurses support" ON)
if(USE_N_CURSES)
    set(CURSES_NEED_NCURSES TRUE)
    set(CURSES_NEED_WIDE TRUE)

    find_package(Curses REQUIRED)
    target_include_directories(intfl PRIVATE ${CURSES_INCLUDE_DIR})
    add_definitions(-DUSE_N_CURSES)
    target_link_libraries(intfl PRIVATE ${CURSES_LIBRARIES})
endif()
