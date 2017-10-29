set(EXPLORER_NAME module_explorer)

set(SOURCE_FILES
  ./sources/client/modules/ModuleExplorer.cpp)
add_library(${EXPLORER_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${EXPLORER_NAME} ${Boost_LIBRARIES})

target_include_directories(${EXPLORER_NAME} PUBLIC
    ./sources/
)
