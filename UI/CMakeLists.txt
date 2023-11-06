cmake_minimum_required(VERSION 3.6.2)
project(GUI)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (USE_SOUND)
    add_definitions(-D SOUND_ON)
    set(QT_USE_QMULTIMEDIA TRUE)
    # sudo apt-get install gstreamer0.10-plugins-good
    find_package(Qt5Multimedia REQUIRED)
endif (USE_SOUND)
#find_package(Qt5Widgets) # in the main CmakeLists else compilation error
find_package(Qt5 COMPONENTS SerialPort REQUIRED)

file(GLOB SOURCES "*.cpp")

#add_library(${PROJECT_NAME} ${SOURCES} LioTest.ui)
add_library(${PROJECT_NAME}  NordendGUI.cpp)
#add_library(${PROJECT_NAME} XstratoWindow.cpp Xstrato.ui)
#add_library(${PROJECT_NAME} SecondWindow.cpp LioTest.ui propgsgui.cpp propgsgui.h propgsgui.ui)


target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        Qt5::Gui
        Qt5::Core
        Qt5::SerialPort # sudo apt-get install libqt5serialport5-dev
        )
if (USE_SOUND)
    target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)
endif (USE_SOUND)
target_link_libraries(${PROJECT_NAME} CapsuleLib)

if (RUNNING_ON_RPI)
    target_link_libraries(${PROJECT_NAME} wiringPi) # control GPIO of RPi
    target_link_libraries(${PROJECT_NAME} crypt) # link crypt
endif (RUNNING_ON_RPI)


