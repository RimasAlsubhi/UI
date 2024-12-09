cmake_minimum_required(VERSION 3.16)
 project(WaterQualityMonitor VERSION 1.0) 
 
 set(CMAKE_CXX_STANDARD 17) 
 
 set(CMAKE_CXX_STANDARD_REQUIRED ON) 
 set(CMAKE_AUTOMOC ON) 
 set(CMAKE_AUTORCC ON) 
 set(CMAKE_AUTOUIC ON) 

 find_package(Qt6 COMPONENTS 
    Core 
    Gui 
    Widgets 
    Charts 
    REQUIRED
) 
 
 add_executable(WaterQualityMonitor 
    main.cpp 
    mainwindow.cpp 
    dashboardwidget.cpp 
    mainwindow.hpp 
    dashboardwidget.hpp
) 
 
 target_link_libraries(WaterQualityMonitor 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    Qt6::Charts 
)