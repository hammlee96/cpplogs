
cmake_minimum_required (VERSION 3.8)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CPPLOGS_OPTION_COMPILE_GRPC "gRPC compile option" ON)

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
	#target_compile_definitions(${CPPLOGS_PJNAME} PRIVATE CPPLOGS_DEF_PLATFORM_WINDOWS)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
	set(CPPLOGS_PLATFORM_LINUX true)
	#target_compile_definitions(CPPLOGS_PJNAME PRIVATE CPPLOGS_DEF_PLATFORM_LINUX)
endif()

project (${CPPLOGS_PJNAME})

set(CPPLOGS_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CPPLOGS_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CPPLOGS_PROTOBUF_FILES_DIRECTORY ${CPPLOGS_SOURCE_DIRECTORY}/src/scripts/proto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CPPLOGS_OUTPUT_DIRECTORY})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

# gRPC source code compile relate
set(CPPLOGS_GRPC_SOURCE_DIRECTORY ${CPPLOGS_SOURCE_DIRECTORY}/src/third_party/grpc)
set(CPPLOGS_GRPC_OUTPUT_DIRECTORY thirty_party/grpc)
set(CPPLOGS_PROTOBUF_SOURCE_DIRECTORY ${CPPLOGS_GRPC_SOURCE_DIRECTORY}/third_party/protobuf)
set(CPPLOGS_ABSL_SOURCE_DIRECTORY ${CPPLOGS_GRPC_SOURCE_DIRECTORY}/third_party/abseil-cpp)
set(CPPLOGS_GRPC_INCLUDE_DIRECTORY ${CPPLOGS_GRPC_SOURCE_DIRECTORY}/include)
set(CPPLOGS_PROTOBUF_INCLUDE_DIRECTORY ${CPPLOGS_PROTOBUF_SOURCE_DIRECTORY}/src)
set(CPPLOGS_ABSL_INCLUDE_DIRECTORY ${CPPLOGS_ABSL_SOURCE_DIRECTORY})

if(CPPLOGS_OPTION_COMPILE_GRPC)
	message("gRPC compile on")
	include(cmake/grpc.cmake)
else()
	message("gRPC compile off")
endif()

# find proto
file(GLOB CPPLOGS_PROTO_FILES ${CPPLOGS_PROTOBUF_FILES_DIRECTORY}/*.proto)
foreach(CPPLOGS_PROTO_FILE ${CPPLOGS_PROTO_FILES})
	# get origin file path and name length
	string(LENGTH ${CPPLOGS_PROTO_FILE} CPPLOGS_PROTO_FILE_LENGTH)
	# delete the end of 6 byte
	math(EXPR CPPLOGS_PROTO_FILE_NEW_LENGTH "${CPPLOGS_PROTO_FILE_LENGTH} - 6")
	string(SUBSTRING ${CPPLOGS_PROTO_FILE} 0 ${CPPLOGS_PROTO_FILE_NEW_LENGTH} CPPLOGS_PROTO_FILE_MODIFY)
	
	# display modified file path and name
	list(APPEND CPPLOGS_PROTO_FILE_SOURCES
	${CPPLOGS_PROTO_FILE_MODIFY}.pb.cc
	${CPPLOGS_PROTO_FILE_MODIFY}.grpc.pb.cc)
	list(APPEND CPPLOGS_PROTO_FILE_HEADERS
	${CPPLOGS_PROTO_FILE_MODIFY}.pb.h
	${CPPLOGS_PROTO_FILE_MODIFY}.grpc.pb.h)
	message(STATUS " - ${CPPLOGS_PROTO_FILE_SOURCES}")
	message(STATUS " - ${CPPLOGS_PROTO_FILE_HEADERS}")
endforeach()

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include
					${CPPLOGS_PROTOBUF_FILES_DIRECTORY}
					${CPPLOGS_GRPC_INCLUDE_DIRECTORY}
					${CPPLOGS_PROTOBUF_INCLUDE_DIRECTORY}
					${CPPLOGS_ABSL_INCLUDE_DIRECTORY})

link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(PROJECT_SOURCES
	src/cpplogs/fileformat.cpp
	src/cpplogs/dataformat.cpp
	src/cpplogs/cpplogsstreamclient.cpp
	src/cpplogs/cpplogsstreamserver.cpp
	src/basetools/toolbox.cpp
	${CPPLOGS_PROTO_FILE_SOURCES})

set(PROJECT_HEADERS
	include/cpplogs/cpplogsw.h
	include/cpplogs/cpplogsr.h
	include/cpplogs/cpplogsstreamclient.h
	include/cpplogs/cpplogsstreamserver.h
	include/cpplogs/error.h
	include/cpplogs/fileformat.h
	include/cpplogs/dataformat.h
	include/cpplogs/timestamp.h
	include/cpplogs/base.h
	include/cpplogs/toolbox.h
	${CPPLOGS_PROTO_FILE_HEADERS})

add_library(${CPPLOGS_PJNAME} 
			STATIC
			${PROJECT_HEADERS}
			${PROJECT_SOURCES})

target_link_libraries(${CPPLOGS_PJNAME}
						absl_flags.lib
						absl_flags_parse.lib
						grpc.lib
						libprotobufd.lib)
	
add_subdirectory(examples/ExampleWriteLog)
add_subdirectory(examples/ExampleReadLog)
