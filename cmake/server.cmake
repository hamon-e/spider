include_directories(SYSTEM ${LIBMONGOCXX_INCLUDE_DIR})
include_directories(SYSTEM ${LIBBSONCXX_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})

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

add_executable(${EXE_SERVER_NAME} ${SOURCE_FILES})

target_include_directories(${EXE_SERVER_NAME} PUBLIC
    ./sources
    ./libs
)

target_link_libraries(${EXE_SERVER_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${LIBBSONCXX_LIBRARIES})
target_link_libraries(${EXE_SERVER_NAME} ${OPENSSL_LIBRARIES})
