#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(EXE_SERVER_NAME spider_serveur)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(SOURCE_FILES ./sources/server/main.cpp)
add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})

if (WIN32)
find_package(OPENSSL)
else()
find_package(PkgConfig)
pkg_search_module(OPENSSL REQUIRED openssl)
endif()

find_package(Boost 1.36.0 COMPONENTS date_time filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################
set(EXE_CLIENT_NAME spider_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_FILES ./sources/ssl/ssl.cpp ./sources/ssl/Base64.cpp ./sources/ssl/CryptAES.cpp ./sources/ssl/CryptRSA.cpp)
if (WIN32)
  set (SOURCE_FILES ${SOURCE_FILES} ./sources/ssl/applink.c)
endif()

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})
target_link_libraries(${EXE_CLIENT_NAME} ${OPENSSL_LIBRARIES})
target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})
