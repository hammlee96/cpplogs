cmake_minimum_required(VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(${PJNAME})

set(PJNAME
	ExampleWriteLog)

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(LIBSNAME
	CppLogs.lib)

set(PJ_SOURCES
	ExampleWriteLog.h
	ExampleWriteLog.cpp)

add_executable(${PJNAME} ${PJ_SOURCES})
target_link_libraries(${PJNAME} ${LIBSNAME})