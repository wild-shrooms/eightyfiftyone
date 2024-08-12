cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(eightyfiftyone)

add_executable(8051-disassembler)
target_include_directories(8051-disassembler PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(8051-disassembler PRIVATE
	src/disassembler/main.cpp
	src/disassembler/disassembler.cpp
)
