cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(main)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	src/main.cpp
)
