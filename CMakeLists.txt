#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(EXE_SERVER_NAME spider_serveur)

find_package(Boost 1.36.0 COMPONENTS date_time filesystem system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(SOURCE_FILES
./sources/server/main.cpp
./sources/server/AUdpServer.cpp
./sources/server/Server.cpp
)

add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})

#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################

set(EXE_CLIENT_NAME spider_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread")

set(SOURCE_FILES
./sources/client/main.cpp
./sources/client/UdpClient.cpp
)

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXE_SERVER_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})
endif()
