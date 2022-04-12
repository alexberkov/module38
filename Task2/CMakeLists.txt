cmake_minimum_required(VERSION 3.21)
project(Task38_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        WebEngineWidgets
        REQUIRED)

add_executable(Task38_2 main.cpp)
target_link_libraries(Task38_2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebEngineWidgets
        )

