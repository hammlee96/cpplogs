
cmake_minimum_required (VERSION 3.8)

option(CPPLOGS_COMPILE_STATIC_OPTION "Whether to compile in static compilation mode" ON)
option(CPPLOGS_COMPILE_EXAMPLE_OPTION "Enable Compilation Example" ON)

message("-- CPPLOGS_COMPILE_STATIC_OPTION: ${CPPLOGS_COMPILE_STATIC_OPTION}")
message("-- CPPLOGS_COMPILE_EXAMPLE_OPTION: ${CPPLOGS_COMPILE_EXAMPLE_OPTION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_COMPILE g++)
set(CMAKE_C_COMPILE gcc)

set(PJNAME_CPPLOGS
	cpplogs)
	
set(CPPLOGS_PLATFORM_WINDOWS False)
set(CPPLOGS_PLATFORM_LINUX False)
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
set(CPPLOGS_PLATFORM_WINDOWS True)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
set(CPPLOGS_PLATFORM_LINUX True)
endif()

project (${PJNAME_CPPLOGS})

set(CPPLOGS_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CPPLOGS_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include
					${CPPLOGS_SOURCE_DIRECTORY}/src)

set(PROJECT_SOURCES
	src/cpplogs/basetools/cppjson.cpp
	src/third_party/cJSON/cJSON.c)

set(PROJECT_HEADERS
	include/cpplogs/basetools/timestamp.h
	include/cpplogs/basetools/error.h
	include/cpplogs/basetools/base.h
	include/cpplogs/basetools/toolbox.h
	include/cpplogs/basetools/cppjson.h
	include/cpplogs/basetools/net/sockettcp.h
	include/cpplogs/dataformat.h
	include/cpplogs/fileformat.h
	include/cpplogs/cpplogsw.h
	include/cpplogs/cpplogsr.h
	include/cpplogs/cpplogsstreamclient.h
	include/cpplogs/cpplogsmessage.h
	src/third_party/cJSON/cJSON.h)

if(${CPPLOGS_COMPILE_STATIC_OPTION})
	set(CPPLOGS_COMPILE_MODE "STATIC")
else()
	set(CPPLOGS_COMPILE_MODE "SHARED")
endif()
message("-- build mode: ${CPPLOGS_COMPILE_MODE}")
add_library(${PJNAME_CPPLOGS} 
			${CPPLOGS_COMPILE_MODE}
			${PROJECT_HEADERS}
			${PROJECT_SOURCES})
if(${CPPLOGS_COMPILE_EXAMPLE_OPTION})
	add_subdirectory(examples/CppLogsWriteLog)
	add_subdirectory(examples/CppLogsReadLog)
	add_subdirectory(examples/CppLogsStreamClient)
endif()
