set(FILE_NAME module_file)

set(SOURCE_FILES
  ./sources/client/modules/ModuleFile.cpp
  ./sources/ssl/Base64.cpp)
add_library(${FILE_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${FILE_NAME} ${Boost_LIBRARIES})

target_include_directories(${FILE_NAME} PUBLIC
    ./sources/
)
