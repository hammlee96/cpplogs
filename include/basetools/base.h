#pragma once

#if defined(_WIN32)
#define CPPLOGS_API __declspec(dllexport)
#else
#define CPPLOGS_API
#endif

#define CPPLOGS_EXTNAME				".cpplog"

#define CPPLOGS_DEBUG				std::cout<<"\n\033[1m\033[32m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_WARNING				std::cout<<"\n\033[1m\033[33m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "
#define CPPLOGS_ERROR				std::cout<<"\n\033[1m\033[31m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "