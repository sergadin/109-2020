cmake_minimum_required(VERSION 3.1)

project(N2_Client)

include_directories(${PROJECT_SOURCE_DIR})

set(Client_SRC main.cpp connector.cpp autotest.cpp)
set(Client_HDR connector.h autotest.h)

add_executable(${PROJECT_NAME} ${Client_SRC} ${Client_HDR})