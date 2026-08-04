cmake_minimum_required(VERSION 3.21)

project(BookManagerQt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(BookManagerQt WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
    book.h
)

target_link_libraries(BookManagerQt PRIVATE Qt6::Widgets)

if(MSVC)
    target_compile_options(BookManagerQt PRIVATE /utf-8)
endif()

set_target_properties(BookManagerQt PROPERTIES
    WIN32_EXECUTABLE TRUE
)
