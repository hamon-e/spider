#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(EXE_SERVER_NAME spider_serveur)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(SOURCE_FILES ./sources/server/main.cpp)
add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})


#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################
set(EXE_CLIENT_NAME spider_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_FILES ./sources/client/main.cpp)

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})
