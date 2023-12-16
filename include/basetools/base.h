#pragma once

#if defined(_WIN32)
#define CPPLOGS_API __declspec(dllexport)
#else
#define CPPLOGS_API
#endif

#define CPPLOGS_DEBUG				std::cout<<"\033[1m\033[32m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "<<std::endl
#define CPPLOGS_WARNING				std::cout<<"\033[1m\033[33m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "<<std::endl
#define CPPLOGS_ERROR				std::cout<<"\033[1m\033[31m"<<"["<<__FILE__<<": "<<__LINE__<<"] "<<__FUNCTION__<<": "<<std::endl