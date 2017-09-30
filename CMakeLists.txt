#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(BIN_NAME spider_serveur)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES ./server/sources/main.cpp)
add_executable(${BIN_NAME} ${SOURCE_FILES})


#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################
project(cpp_spider)
set(BIN_NAME spider_client)

#SET(CMAKE_CXX_COMPILER /path/to/cpp/compiler)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES ./client/sources/main.cpp)

add_executable(${BIN_NAME} ${SOURCE_FILES})