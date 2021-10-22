cmake_minimum_required(VERSION 3.0)

project(Engine-JS)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")


add_subdirectory(src/corejs)

add_executable(Engine-JS src/main.cpp)
target_link_libraries(Engine-JS corejs)

target_include_directories(corejs PUBLIC "src/corejs")

