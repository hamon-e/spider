if(WIN32)
  set(BOOST_ROOT "C:/local/boost_1_65_1")
  link_directories("${BOOST_ROOT}/lib64-msvc-14.1")

  find_package(OPENSSL)
elseif(APPLE)
  find_package(OPENSSL)
else()
  find_package(PkgConfig)
  pkg_search_module(OPENSSL REQUIRED openssl)
endif()

find_package(Boost REQUIRED COMPONENTS thread chrono date_time filesystem system )
