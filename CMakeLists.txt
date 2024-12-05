cmake_minimum_required(VERSION 3.16)

project(WaterQualityMonitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

qt_add_executable(WaterQualityMonitor
    main.cpp
    mainwindow.cpp
    dashboardwidget.cpp
    dashboardwidget.hpp
    mainwindow.hpp
)

target_link_libraries(WaterQualityMonitor PRIVATE Qt6::Widgets Qt6::Charts)
