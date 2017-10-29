find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

include_directories(SYSTEM "/usr/local/include/mongocxx/v_noabi")
include_directories(SYSTEM "/usr/local/include/bsoncxx/v_noabi")
include_directories(SYSTEM "/usr/local/lib")
