cmake_minimum_required(VERSION 3.26)
project(Left4Dead TPG Taller)

set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D_POSIX_C_SOURCE=200809L")

set(COMMON_DIR common)
set(CLIENT_DIR client)
set(SERVER_DIR server)
set(TARGET_DIR target)

file(GLOB COMMON_SRCS ${COMMON_DIR}/*.cpp)
file(GLOB CLIENT_SRCS ${CLIENT_DIR}/*.cpp)
file(GLOB SERVER_SRCS ${SERVER_DIR}/*.cpp)

add_executable(executable ${COMMON_SRCS} ${CLIENT_SRCS} ${SERVER_SRCS})

set_target_properties(executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
)
