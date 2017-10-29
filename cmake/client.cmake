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
    ./sources/client/WinTools.cpp
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
