cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(intfl)

option(USE_N_CURSES "Use ncurses library for UI" OFF)

add_executable(intfl src/main.cpp)
target_include_directories(
    intfl PRIVATE "include"
)

if(USE_N_CURSES)
    set(CURSES_NEED_NCURSES TRUE)
    set(CURSES_NEED_WIDE TRUE)

    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    add_definitions(-DUSE_N_CURSES)
    target_link_libraries(intfl ${CURSES_LIBRARIES} ncursesw)
endif()
