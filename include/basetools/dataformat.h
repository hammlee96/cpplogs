#include <iostream>

namespace CppLogs {
	class DataFormat {
	public:
		struct StCppLogsItem {
			std::string key;
			std::string secondKey;
			std::string timeStamp;
			std::string fileLine;
			std::string data;
		};

	public:
		DataFormat();
		~DataFormat();

		std::string format_data(const std::string& data);
		DataFormat::StCppLogsItem unformat_data(const std::string& data);
	};
}