cmake_minimum_required(VERSION 3.6.2)
project(ERT2023GS)

###############################################################
# Set the build varialble to ON or OFF on your need
set(USE_GUI ON)
set(USE_XBEE ON)
set(USE_INFLUXDB OFF)  # use for logging and Grafana
set(RUNNING_ON_RPI OFF) # <-- if not ON, the Ignition hardware won't wrork
set(USE_SOUND OFF)
####
set(USE_LORA OFF)
###############################################################
if (NOT RUNNING_ON_RPI)
    message("/!\\ Ignition Circuit not activated !")
endif ()

set(CMAKE_CXX_STANDARD 14)

# Add sub CmakeLists.txt

# Capsule git submodule library
add_library(CapsuleLib Capsule/src/capsule.h)
# Specify the language for the source files
set_target_properties(CapsuleLib PROPERTIES LINKER_LANGUAGE CXX)

if (USE_XBEE)

    add_executable(AVsimulator src/AVsimulator.cpp)
    add_executable(GSE_PLsimu src/GSE_PLsimu.cpp)
    add_executable(TestPacket src/PacketXTest.cpp)
    add_executable(TEST src/test.cpp)

    if (USE_GUI)
        #find_package(Qt5Widgets)
        find_package(Qt5 COMPONENTS
                Core
                Gui
                Widgets
                SerialPort
                REQUIRED)
        qt5_add_resources(RCC_SOURCES UI/assets.qrc)      # add resources to Gui
        add_subdirectory(UI)
        add_executable(${PROJECT_NAME} ${RCC_SOURCES} src/ERT2020GS.cpp ERT_RF_Protocol_Interface/PacketDefinition.h) # tmp debug !
        #set(CMAKE_AUTOUIC ON) # tmp
        add_executable(FancyGUI ${RCC_SOURCES} src/FancyGUI.cpp )#LioTest.ui)
        add_executable(PropGS ${RCC_SOURCES} src/MainProp.cpp)
        add_executable(XSTRATO ${RCC_SOURCES} src/XSTRATO.cpp)
        add_executable(Nordend ${RCC_SOURCES} src/Nordend.cpp)

        #set(ENV{DISPLAY} :0) #maybe try this later
    endif (USE_GUI)

endif (USE_XBEE)

############# link librarie to targets #######################
if (USE_XBEE)

    add_executable(XbeeTest src/XbeeTest.cpp)
    include_directories(RFmodem/lib/serial/include/)
    target_link_libraries(XbeeTest serial)

    if (USE_GUI)
        target_link_libraries(${PROJECT_NAME} GUI)
        target_link_libraries(FancyGUI GUI)
        target_link_libraries(PropGS GUI)
        target_link_libraries(PropGS Qt5SerialPort)
        target_link_libraries(XSTRATO GUI)
        target_link_libraries(XSTRATO Qt5SerialPort)
        target_link_libraries(XSTRATO CapsuleLib)
        target_link_libraries(Nordend GUI)
        target_link_libraries(Nordend Qt5SerialPort)
        target_link_libraries(Nordend CapsuleLib)

        target_include_directories(${PROJECT_NAME} PUBLIC UI)
        target_include_directories(FancyGUI PUBLIC UI)
        target_include_directories(PropGS PUBLIC UI)
        target_include_directories(XSTRATO PUBLIC UI)
        target_include_directories(XSTRATO PUBLIC Capsule/src/)
        target_include_directories(Nordend PUBLIC UI)
        target_include_directories(Nordend PUBLIC Capsule/src/)
    endif (USE_GUI)

endif (USE_XBEE)

if (USE_INFLUXDB)
    find_package(InfluxDB)
#    find_package(cpr)
    add_executable(influxDBexe src/influxdb.cpp)
#    target_link_libraries(influxDBexe PRIVATE cpr::cpr PUBLIC CURL::libcurl)
    target_link_libraries(influxDBexe PRIVATE InfluxData::InfluxDB)
endif (USE_INFLUXDB)