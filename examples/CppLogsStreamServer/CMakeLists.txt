cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PJNAME_EXAMPLE
	cpplogs_streamserver)

project(${PJNAME_EXAMPLE})

include_directories(${CPPLOGS_SOURCE_DIRECTORY}/include)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

if(${CPPLOGS_PLATFORM_WINDOWS})
	set(LIBSNAME_EXAMPLE
		${PJNAME_CPPLOGS}
	)
else()
	set(LIBSNAME_EXAMPLE
		-l${PJNAME_CPPLOGS}
		-lpthread
	)
endif()

add_executable(${PJNAME_EXAMPLE} CppLogsStreamServer.h CppLogsStreamServer.cpp cthreadbase.h cthreadbase.cpp cthreadpool.h command_handler.h command_handler.cpp)
target_link_libraries(${PJNAME_EXAMPLE} ${LIBSNAME_EXAMPLE})