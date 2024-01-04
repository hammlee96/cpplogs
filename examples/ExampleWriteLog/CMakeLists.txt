cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PJNAME_WRITE
	ExampleWriteLog)

project(${PJNAME_WRITE})

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(LIBSNAME_WRITE
	${CPPLOGS_PJNAME})

add_executable(${PJNAME_WRITE} ExampleWriteLog.h ExampleWriteLog.cpp)
target_link_libraries(${PJNAME_WRITE} ${LIBSNAME_WRITE})