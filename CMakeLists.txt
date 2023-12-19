
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PJNAME
	CppLogs)

project (${PJNAME})

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include/cpplogs
					include/basetools)
set(PROJECT_SOURCES
	src/cpplogs/fileformat.cpp
	src/basetools/toolbox.cpp)

set(PROJECT_HEADERS
	include/cpplogs/cpplogsw.h
	include/cpplogs/error.h
	include/cpplogs/fileformat.h
	include/basetools/base.h
	include/basetools/toolbox.h)

add_library(${PJNAME} 
			STATIC
			${PROJECT_HEADERS}
			${PROJECT_SOURCES})
	
add_subdirectory(examples/ExampleWriteLog)
