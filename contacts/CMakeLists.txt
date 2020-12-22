cmake_minimum_required(VERSION 3.17)
project(contacts C)

set(CMAKE_C_STANDARD 11)

add_executable(contacts main.c sqlite3.c)
add_compile_options(-l sqlite3)
target_link_libraries(contacts ${CMAKE_DL_LIBS})