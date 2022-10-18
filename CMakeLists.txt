
cmake_minimum_required(VERSION 3.23)
project(zip-test)

add_executable(
    zip-test
    src/main.cpp
    )

target_compile_features(
    zip-test
    PRIVATE
    cxx_std_17
    )

find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system iostreams)

target_link_libraries(
    zip-test
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    )



