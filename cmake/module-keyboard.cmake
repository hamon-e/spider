set(KEYBOARD_NAME module_keyboard)

set(SOURCE_FILES sources/client/modules/ModuleKeyboard.cpp sources/client/IModule.hpp)
add_library(${KEYBOARD_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${KEYBOARD_NAME} ${Boost_LIBRARIES})
