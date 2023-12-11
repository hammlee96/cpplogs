#pragma once

#if defined(_WIN32)
#define CPPLOGS_API __declspec(dllexport)
#else
#define CPPLOGS_API
#endif