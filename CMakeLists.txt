
cmake_minimum_required (VERSION 3.8)

set(PJNAME
	CppLogs)

project (${PJNAME})

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include/cpplogs
					include/basetools)
set(PROJECT_SOURCES
	src/cpplogs/cpplogs.cpp
	src/basetools/toolbox.cpp)

set(PROJECT_HEADERS
	include/cpplogs/cpplogs.h
	include/cpplogs/error.h
	include/cpplogs/base.h
	include/basetools/toolbox.h)

add_library(${PJNAME} 
			STATIC
			${PROJECT_HEADERS}
			${PROJECT_SOURCES})
add_subdirectory(examples/ExampleWriteLog)
