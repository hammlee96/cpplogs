#pragma once
#include "base.h"
#include <chrono>

namespace CppLogs {
	class CPPLOGS_API TimeStamp {
	public:
		TimeStamp(const std::string& mark) : _mark(mark)
		{
			_start = std::chrono::steady_clock::now();
		}
		double get_duration()
		{
			std::chrono::duration<double> duration = std::chrono::steady_clock::now() - _start;
			return duration.count();
		}
		~TimeStamp()
		{
			CPPLOGS_DEBUG << _mark<<": " << get_duration();
		}
	private:
		std::chrono::steady_clock::time_point _start;
		const std::string _mark;
	};
}