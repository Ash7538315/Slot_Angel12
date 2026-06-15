cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ANGEL12)

# src
set(SOURCES
    src/main.cpp
    src/ReelCtrl.cpp
    src/FlagLottery.cpp
)

add_executable(Angel12.x
    ${SOURCES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
target_include_directories(Angel12.x PRIVATE ${CMAKE_SOURCE_DIR}/include)
