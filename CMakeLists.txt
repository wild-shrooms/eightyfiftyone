cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(eightyfiftyone)
add_executable(disassembler)

target_include_directories(disassembler PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_sources(disassembler PRIVATE
	src/disassembler/main.cpp
	src/disassembler/Disassembler.cpp
)
