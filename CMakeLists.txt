cmake_minimum_required(VERSION 3.6)
project(cpp_spider)

set(BOOST_ROOT "C:/local/boost_1_65_1")
find_package(Boost REQUIRED COMPONENTS thread chrono date_time filesystem system )
include_directories(${Boost_INCLUDE_DIRS})
link_directories("${BOOST_ROOT}/lib64-msvc-14.1")

#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

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

set(SOURCE_FILES ./sources/client/main.cpp sources/client/ModuleManager.cpp sources/client/ModuleCommunication.cpp)
set(SOURCE_FILES ./sources/ssl/ssl.cpp ./sources/ssl/Base64.cpp ./sources/ssl/CryptAES.cpp ./sources/ssl/CryptRSA.cpp)
if (WIN32)
  set (SOURCE_FILES ${SOURCE_FILES} ./sources/ssl/applink.c)
endif()

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})
target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_CLIENT_NAME} ${OPENSSL_LIBRARIES})
if (WIN32)
else()
    target_link_libraries(${EXE_CLIENT_NAME} "dl")
endif()

#############################################################################
#############  Cmake CLIENT MODULE : KEYBOARD  ##############################
#############################################################################

set(KEYBOARD_NAME module_keyboard)

set(SOURCE_FILES sources/client/modules/ModuleKeyboard.cpp sources/client/IModule.hpp)
add_library(${KEYBOARD_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${KEYBOARD_NAME} ${Boost_LIBRARIES})
