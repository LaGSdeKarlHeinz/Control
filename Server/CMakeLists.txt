cmake_minimum_required(VERSION 3.16)
project(FirehornServer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Find the required Qt6 components
find_package(Qt6 COMPONENTS Widgets Core Network SerialPort  REQUIRED)

add_library(CapsuleLib Capsule/src/capsule.h)

set(SOURCES_SERVER
    src/server.cpp
    src/main.cpp
    src/RequestAdapter.cpp
    src/network/RequestHandler.cpp
    ../GUI/src/network-utils/ClientManager.cpp
    ../GUI/src/network-utils/RequestBuilder.cpp
)

set(HEADERS_SERVER
    include/Server.h 
    include/RequestHandler.h
    include/RequestAdapter.h
    ../GUI/include/ClientInterface.h
    ../GUI/include/ClientManager.h
    ../GUI/include/RequestBuilder.h 
)

add_executable(${PROJECT_NAME} ${SOURCES_SERVER} ${HEADERS_SERVER})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../GUI/include)


target_link_libraries(${PROJECT_NAME} PRIVATE
                        Qt6::Widgets 
                        Qt6::Core
                        Qt6::Network
                        Qt6::SerialPort
                        )