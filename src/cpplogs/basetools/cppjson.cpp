#include "cpplogs/basetools/cppjson.h"
#include "third_party/cJSON/cJSON.h"

namespace CppLogs
{
	CppJson::CppJson()
	{
		_pmonitor = nullptr;
	}

	CppJson::~CppJson()
	{
	}

	void CppJson::Clear()
	{
		if (_pmonitor) {
			cJSON_Delete(_pmonitor);
			delete _pmonitor;
			_pmonitor = nullptr;
		}
	}

	bool CppJson::Add(const std::string& key, const std::string& value)
	{
		cJSON* pLocalMonitor = _get_valid_object();

		if (pLocalMonitor == NULL)
		{
			return false;
		}
		if (pLocalMonitor->type != cJSON_Object)
		{
			return false;
		}

		if (cJSON_GetObjectItem(pLocalMonitor, value) != NULL) {
			return false;
		}
		cJSON* pJsonStruct = cJSON_CreateString(value);
		if (pJsonStruct == nullptr) {
			return false;
		}
		cJSON_AddItemToObject(pLocalMonitor, key, pJsonStruct);

		if (cJSON_GetObjectItem(pLocalMonitor, value) == NULL) {
			return false;
		}

		return true;
	}

	bool CppJson::Add(const std::string& key, const int& value)
	{
		return false;
	}

	bool CppJson::Add(const std::string& key, const float& value)
	{
		return false;
	}
	cJSON* CppJson::_get_valid_object()
	{
		if (_pmonitor == nullptr) {
			_pmonitor = new cJSON_CreateObject();
			return _pmonitor;
		}
		else {
			return _pmonitor;
		}
		return nullptr;
	}
}