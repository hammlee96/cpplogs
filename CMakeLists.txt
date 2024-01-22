
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_COMPILE g++)
set(CMAKE_C_COMPILE gcc)

set(CPPLOGS_PJNAME
	cpplogs)
	
set(CPPLOGS_PLATFORM_WINDOWS false)
set(CPPLOGS_PLATFORM_LINUX false)
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
set(CPPLOGS_PLATFORM_WINDOWS true)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
set(CPPLOGS_PLATFORM_LINUX true)
endif()

project (${CPPLOGS_PJNAME})

set(CPPLOGS_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CPPLOGS_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include)

set(PROJECT_SOURCES
	src/cpplogs/basetools/toolbox.cpp
	src/cpplogs/dataformat.cpp
	src/cpplogs/cpplogsstreamclient.cpp
	src/cpplogs/cpplogsstreamserver.cpp)

set(PROJECT_HEADERS
	include/cpplogs/basetools/timestamp.h
	include/cpplogs/basetools/error.h
	include/cpplogs/basetools/base.h
	include/cpplogs/basetools/toolbox.h
	include/cpplogs/basetools/net/sockettcp.h
	include/cpplogs/dataformat.h
	include/cpplogs/fileformat.h
	include/cpplogs/cpplogsw.h
	include/cpplogs/cpplogsr.h
	include/cpplogs/cpplogsstreamclient.h
	include/cpplogs/cpplogsstreamserver.h)

add_library(${CPPLOGS_PJNAME} 
			STATIC
			${PROJECT_HEADERS}
			${PROJECT_SOURCES})
	
add_subdirectory(examples/ExampleWriteLog)
add_subdirectory(examples/ExampleReadLog)
