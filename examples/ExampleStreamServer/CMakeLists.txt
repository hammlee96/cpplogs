cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PJNAME_STREAMSERVER
	ExampleStreamServer)

project(${PJNAME_STREAMSERVER})

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(LIBSNAME_WRITE
	${CPPLOGS_PJNAME})

add_executable(${PJNAME_STREAMSERVER} ExampleStreamServer.h ExampleStreamServer.cpp)
target_link_libraries(${PJNAME_STREAMSERVER} ${LIBSNAME_WRITE})