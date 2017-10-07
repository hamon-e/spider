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
find_package(Boost 1.36.0 COMPONENTS date_time filesystem system thread)

if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})

    set(SOURCE_FILES sources/LocalDB.cpp sources/LocalDB.hpp sources/main.cpp)

    add_executable(${EXE_CLIENT_NAME} ${SOURCE_FILES})

    target_link_libraries(${EXE_CLIENT_NAME} ${Boost_LIBRARIES})

endif()
