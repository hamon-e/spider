
cmake_minimum_required(VERSION 3.6)
project(test_mgDBcXXX)
#[[
find_package(mongocxx)

set(SOURCE_FILES
    main.cpp)

add_executable(test_mgDBcXXX ${SOURCE_FILES})
]]

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(Boost 1.36.0 COMPONENTS system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

set(SOURCE_FILES main.cpp)
add_executable(test_mgDBcXXX ${SOURCE_FILES})

target_link_libraries(test_mgDBcXXX ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(test_mgDBcXXX ${LIBBSONCXX_LIBRARIES})
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(test_mgDBcXXX ${Boost_LIBRARIES})
endif()
