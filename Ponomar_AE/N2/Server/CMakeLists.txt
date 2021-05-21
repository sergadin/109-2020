cmake_minimum_required(VERSION 3.1)

project(N2_Server)

include_directories(${PROJECT_SOURCE_DIR})

set(Server_SRC main.cpp server.cpp database.cpp)
set(TASK_3_HDR server.h database.h)

add_executable(${PROJECT_NAME} ${TASK_3_SRC} ${TASK_3_HDR})