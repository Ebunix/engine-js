cmake_minimum_required(VERSION 3.0)

project(Engine-JS)

add_subdirectory(src/corejs)

add_executable(Engine-JS src/main.cpp)
target_link_libraries(Engine-JS corejs)
target_link_libraries(Engine-JS /usr/lib/libc++.a)

target_include_directories(corejs PUBLIC "src/corejs")

