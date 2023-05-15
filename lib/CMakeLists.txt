add_library(ssl_wrapper)

target_sources(ssl_wrapper PUBLIC ssl_wrapper.c)
target_include_directories(ssl_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenSSL REQUIRED)

target_link_libraries(ssl_wrapper PRIVATE OpenSSL::Crypto)