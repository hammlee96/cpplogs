#pragma once

#if defined(_WIN32)
#define CPPLOGS_API			__declspec(dllexport)
#define CPPLOGS_SYSTEM_WINDOWS
#else
#define CPPLOGS_API
#define CPPLOGS_SYSTEM_LINUX
#endif

#if defined(CPPLOGS_SYSTEM_WINDOWS)
#define CPPLOGS_DISABLE4251(_DISABLE4521TYPE) \
					__pragma(warning(push)) \
					__pragma(warning(disable:4251)) \
					_DISABLE4521TYPE;\
					__pragma(warning(pop)) 
#else
#define CPPLOGS_DISABLE4251(...)
#endif
					
#define CPPLOGS_EXTNAME						".cpplog"

#define CPPLOGS_DEBUG						std::cout<<"\n\033[1m\033[32m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_WARNING						std::cout<<"\n\033[1m\033[33m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_ERROR						std::cout<<"\n\033[1m\033[31m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "

#define CPPLOGS_DEF_CPPLOGS_TRUE			"y"
#define CPPLOGS_DEF_CPPLOGS_FALSE			"n"

#define CPPLOGS_DEF_HEADER					"header"
#define CPPLOGS_DEF_HEADER_CREATE_TIME		"create_time"
#define CPPLOGS_DEF_HEADER_LEVEL			"level"
#define CPPLOGS_DEF_HEADER_INFO				"info"
#define CPPLOGS_DEF_HEADER_WARN				"warn"
#define CPPLOGS_DEF_HEADER_ERROR			"error"
#define CPPLOGS_DEF_HEADER_TIME_STAMP		"time_stamp"

#define CPPLOGS_STR_COMMOND					"commond"
#define CPPLOGS_STR_SET_FILEINFO			"set_fileinfo"
#define CPPLOGS_STR_SET_LOGTYPE				"set_log_type"
#define CPPLOGS_STR_SET_LOGDATA				"set_log_data"

#define CPPLOGS_STR_FILEPATHNAME			"file_path_name"
#define CPPLOGS_STR_KEY						"key"
#define CPPLOGS_STR_ENUM_KEY				"enum_key"
#define CPPLOGS_STR_SECOND_KEY				"second_key"
#define CPPLOGS_STR_TIME_STAMP				"time_stamp"
#define CPPLOGS_STR_DATA					"data"
#define CPPLOGS_STR_FORMATTED_DATA			"formatted_data"
