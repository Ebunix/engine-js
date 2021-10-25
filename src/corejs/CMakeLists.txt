add_library(corejs
    corejs.cpp
    funcs.cpp)
    
add_compile_definitions(V8_COMPRESS_POINTERS)
add_compile_definitions(V8_31BIT_SMIS_ON_64BIT_ARCH)

set(THREADS_PREFER_PTHREAD_FLAG ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Using V8 debug objects")
    set(V8_DIR "${CMAKE_SOURCE_DIR}/v8/v8/out.gn/x64.debug/obj" CACHE INTERNAL "V8 object directory" FORCE)
else()
    message(STATUS "Using V8 release objects")
    set(V8_DIR "${CMAKE_SOURCE_DIR}/v8/v8/out.gn/x64.release/obj" CACHE INTERNAL "V8 object directory" FORCE)
endif()
mark_as_advanced(V8_DIR)

find_package(Threads REQUIRED)
target_link_libraries(corejs Threads::Threads)
target_link_libraries(corejs ${CMAKE_DL_LIBS})

target_include_directories(corejs PUBLIC "${PROJECT_BINARY_DIR}" "${CMAKE_SOURCE_DIR}/v8/v8/include")

target_link_libraries(corejs ${V8_DIR}/libv8_monolith.a)
target_link_libraries(corejs ${V8_DIR}/libv8_libbase.a)
target_link_libraries(corejs ${V8_DIR}/libv8_libplatform.a)
