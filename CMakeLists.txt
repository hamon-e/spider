#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(EXE_SERVER_NAME spider_serveur)

find_package(Boost 1.36.0 COMPONENTS date_time filesystem system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g3")
set(SOURCE_FILES
./sources/server/main.cpp
./sources/APacketServer.cpp
./sources/AUdpServer.cpp
./sources/PacketManager.cpp
./sources/server/Server.cpp
./sources/UdpEndpoint.cpp
./sources/Packet.cpp
./sources/json.cpp
./sources/MapDB.cpp
)

add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})

target_include_directories(${EXE_SERVER_NAME} PUBLIC
    ./sources
)

#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################

set(EXE_CLIENT_NAME spider_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread")

set(SOURCE_FILES
./sources/client/main.cpp
./sources/UdpEndpoint.cpp
./sources/AUdpServer.cpp
./sources/APacketServer.cpp
./sources/PacketManager.cpp
./sources/client/Client.cpp
./sources/Packet.cpp
./sources/json.cpp
./sources/MapDB.cpp
)

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})

target_include_directories(${EXE_CLIENT_NAME} PUBLIC
    ./sources
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXE_SERVER_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})
endif()
