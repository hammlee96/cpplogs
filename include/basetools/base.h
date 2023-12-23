#pragma once

#if defined(_WIN32)
#define CPPLOGS_API			__declspec(dllexport)
#define CPPLOGS_SYSTEM_WINDOWS
#else
#define CPPLOGS_API
#define CPPLOGS_SYSTEM_LINUX
#endif

#define CPPLOGS_EXTNAME				".cpplog"

#define CPPLOGS_DEBUG				std::cout<<"\n\033[1m\033[32m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_WARNING				std::cout<<"\n\033[1m\033[33m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_ERROR				std::cout<<"\n\033[1m\033[31m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "

#define DEF_CPPLOGS_TRUE			"y"
#define DEF_CPPLOGS_FALSE			"n"

#define DEF_HEADER					"header"
#define DEF_HEADER_CREATE_TIME		"create_time"
#define DEF_HEADER_LEVEL			"level"
#define DEF_HEADER_INFO				"info"
#define DEF_HEADER_WARN				"warn"
#define DEF_HEADER_ERROR			"error"
#define DEF_HEADER_TIME_STAMP		"time_stamp"
#define DEF_HEADER_FILE_LINE		"file_line"
