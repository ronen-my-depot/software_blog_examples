project(ezdaemon)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug) # Release | Debug

ADD_EXECUTABLE (server main_server.cpp Server.cpp)
TARGET_LINK_LIBRARIES (server rt)

ADD_EXECUTABLE (client main_client.cpp)
TARGET_LINK_LIBRARIES (client rt)
