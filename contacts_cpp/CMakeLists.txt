cmake_minimum_required(VERSION 3.17)
project(contacts_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(contacts_cpp main.cpp sqlite3.c)
add_compile_options(-l sqlite3)