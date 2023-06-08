cmake_minimum_required(VERSION 3.26)
project(Left4Dead_Taller_TPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Catch2 3 REQUIRED)


set(COMMON_DIR common)
set(CLIENT_DIR client)
set(SERVER_DIR server)
set(TARGET_DIR target)
set(TESTS_DIR tests)

file(GLOB COMMON_SRCS ${COMMON_DIR}/*.cpp)
file(GLOB CLIENT_SRCS ${CLIENT_DIR}/*.cpp ${CLIENT_DIR}/main/main.cpp)
file(GLOB SERVER_SRCS_FOR_TESTS ${SERVER_DIR}/*.cpp EXCLUDE ${SERVER_DIR}/main)
file(GLOB SERVER_SRCS ${SERVER_DIR}/*.cpp ${SERVER_DIR}/main/main.cpp)
file(GLOB TESTS_SRCS ${TESTS_DIR}/*.cpp)

add_library(common_objects OBJECT ${COMMON_SRCS})

add_executable(client_executable ${COMMON_SRCS} ${CLIENT_SRCS})
target_link_libraries(client_executable PRIVATE Threads::Threads)
target_link_libraries(client_executable PRIVATE SDL2_image)
target_link_libraries(client_executable PRIVATE SDL2)

add_executable(server_executable ${COMMON_SRCS} ${SERVER_SRCS})
target_link_libraries(server_executable PRIVATE Threads::Threads)

add_executable(tests_executable ${COMMON_SRCS} ${SERVER_SRCS_FOR_TESTS} ${TESTS_SRCS})
target_link_libraries(tests_executable PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests_executable PRIVATE Threads::Threads)

set_target_properties(client_executable server_executable PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
)

set_target_properties(client_executable PROPERTIES
OUTPUT_NAME client
)

set_target_properties(server_executable PROPERTIES
OUTPUT_NAME server
)

set_target_properties(tests_executable PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})

set_target_properties(common_objects PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

set_target_properties(client_executable server_executable common_objects tests_executable PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

set(COMMON_OBJ $<TARGET_OBJECTS:common_objects>)
set(CLIENT_OBJ $<TARGET_OBJECTS:common_objects> ${CLIENT_SRCS})
set(SERVER_OBJ $<TARGET_OBJECTS:common_objects> ${SERVER_SRCS})
set(TESTS_OBJ $<TARGET_OBJECTS:common_objects> ${TESTS_SRCS})

add_custom_target(clean_target
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${TARGET_DIR}
  COMMAND ${CMAKE_COMMAND} -E remove ${COMMON_DIR}/*.o ${CLIENT_DIR}/*.o ${SERVER_DIR}/*.o
)

add_custom_target(all_target
  DEPENDS client_executable server_executable
)
