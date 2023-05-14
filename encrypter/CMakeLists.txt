add_executable(encrypter)
target_sources(encrypter PRIVATE main.c)
target_link_libraries(encrypter LINK_PUBLIC ssl_wrapper)