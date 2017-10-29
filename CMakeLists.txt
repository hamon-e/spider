cmake_minimum_required(VERSION 3.0)
project(cpp_spider)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include(./cmake/deps.cmake)

if(${target} STREQUAL "server" OR ${target} STREQUAL "all")
  include(./cmake/server-deps.cmake)
  include(./cmake/server.cmake)
endif()

if (${target} STREQUAL "client" OR ${target} STREQUAL "all")
  include(./cmake/client.cmake)
endif()

if(${target} STREQUAL "modules")
  include(./cmake/module-file.cmake)
  include(./cmake/module-explorer.cmake)
  include(./cmake/module-image.cmake)
  include(./cmake/module-keyboard.cmake)
endif()
