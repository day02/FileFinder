cmake_minimum_required(VERSION 3.10)
project(FileFinder CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    ## sudo sysctl vm.mmap_rnd_bits=30
    set(SANITIZERS "-fsanitize=thread -fno-omit-frame-pointer")
    ##set(SANITIZERS "-fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZERS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZERS}")
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(file-finder main.cpp
                           file_finder.cpp
                           terminal.cpp
                           thread_pool.cpp
                           queue.cpp
                           scheduler.cpp)
