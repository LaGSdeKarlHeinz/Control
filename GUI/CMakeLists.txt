
cmake_minimum_required(VERSION 3.16)
project(FirehornGUI VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Find the required Qt6 components
find_package(Qt6 COMPONENTS Widgets Core Network REQUIRED)

# Add your source files
set(SOURCES_GUI
    src/json/jsoncpp.cpp
    src/network-utils/ClientManager.cpp
    src/views/DataView.cpp
    src/views/GSManagerView.cpp
    src/views/TelemetryView.cpp
    src/main.cpp
    src/MainWindow.cpp
)

set(HEADERS_GUI
    src/Setup.h
    include/json/json-forwards.h
    include/json/json.h
    include/ClientInterface.h 
    include/ClientManager.h
    include/DataView.h
    include/GSManagerView.h
    include/MainWindow.h
    include/TelemetryView.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES_GUI} ${HEADERS_GUI})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link against the Qt6 Widgets module
target_link_libraries(${PROJECT_NAME} PRIVATE 
                        Qt6::Widgets 
                        Qt6::Core
                        Qt6::Network
                        )