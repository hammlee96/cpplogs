cmake_minimum_required(VERSION 3.8)

set(PJNAME
	ExampleWriteLog)

include_directories(../../src/main)
link_directories(../out/build/x64-Debug)

set(LIBSNAME
	CppLogs.lib)

set(PJ_SOURCES
	ExampleWriteLog.h
	ExampleWriteLog.cpp)

project(${PJNAME})


add_executable(${PJNAME} ${PJ_SOURCES})
target_link_libraries(${PJNAME} ${LIBSNAME})