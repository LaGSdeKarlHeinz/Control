cmake_minimum_required(VERSION 3.16)
project(FirehornGUI VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Find the required Qt6 components
find_package(Qt6 COMPONENTS Widgets Core Network REQUIRED)

# Add your source files
set(SOURCES_GUI
    src/main.cpp
    src/views/DataView.cpp
    src/server/server.cpp
    src/network-utils/ClientManager.cpp 
    src/json/jsoncpp.cpp
    # Add other source files here
)

set(HEADERS_GUI
    include/DataView.h 
    include/Server.h 
    include/ClientInterface.h 
    include/ClientManager.h
    include/json/json.h 
    include/json/json-forwards.h 
)

set(SOURCES_SERVER
    src/server/server.cpp
    src/server/main.cpp    
)

set(HEADERS_SERVER
    include/Server.h 
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES_GUI} ${HEADERS_GUI})
add_executable(Server ${SOURCES_SERVER} ${HEADERS_SERVER})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link against the Qt6 Widgets module
target_link_libraries(${PROJECT_NAME} PRIVATE 
                        Qt6::Widgets 
                        Qt6::Core
                        Qt6::Network
                        )

target_link_libraries(Server PRIVATE 
                        Qt6::Widgets 
                        Qt6::Core
                        Qt6::Network
                        )