add_executable(decrypter)
target_sources(decrypter PRIVATE main.c)
target_link_libraries(decrypter LINK_PUBLIC ssl_wrapper)