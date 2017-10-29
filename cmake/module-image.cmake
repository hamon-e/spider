set(IMAGE_NAME module_image)

set (SOURCE_FILES
  ./sources/client/modules/ModuleImage.cpp)
add_library(${IMAGE_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${IMAGE_NAME} ${Boost_LIBRARIES} gdiplus.lib)

target_include_directories(${IMAGE_NAME} PUBLIC
    ./sources/
)
