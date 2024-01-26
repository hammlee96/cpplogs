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
			::cJSON_Delete(_pmonitor);
			_pmonitor = nullptr;
		}
	}

	bool CppJson::Parse(const std::string& json)
	{
		Clear();
		_pmonitor = ::cJSON_Parse(json.c_str());
		if (_pmonitor == nullptr) {
			return false;
		}
		return true;
	}

	bool CppJson::ToString(std::string & jsonData)
	{
		char* jsonString = nullptr;
		if (_pmonitor == nullptr) {
			return false;
		}
		jsonString = cJSON_Print(_pmonitor);
		if (jsonString == nullptr) {
			return false;
		}
		jsonData = jsonString;
		CppLogs_free(jsonString);
		return true;
	}

	bool CppJson::Get(const std::string& key, std::string& value)
	{
		if (_pmonitor == nullptr) {
			return false;
		}
		cJSON* pLocalMonitor = ::cJSON_GetObjectItem(_pmonitor, key.c_str());
		if (pLocalMonitor == nullptr) {
			return false;
		}
		if (!::cJSON_IsString(pLocalMonitor) || (pLocalMonitor->valuestring == nullptr)) {
			return false;
		}
		value = pLocalMonitor->valuestring;
		return true;
	}

	bool CppJson::Get(const std::string& key, int& value)
	{
		if (_pmonitor == nullptr) {
			return false;
		}
		cJSON* pLocalMonitor = ::cJSON_GetObjectItem(_pmonitor, key.c_str());
		if (pLocalMonitor == nullptr) {
			return false;
		}
		if (!::cJSON_IsNumber(pLocalMonitor)) {
			return false;
		}
		value = pLocalMonitor->valueint;
		return true;
	}

	bool CppJson::Get(const std::string& key, double& value)
	{
		if (_pmonitor == nullptr) {
			return false;
		}
		cJSON* pLocalMonitor = ::cJSON_GetObjectItem(_pmonitor, key.c_str());
		if (pLocalMonitor == nullptr) {
			return false;
		}
		if (!::cJSON_IsNumber(pLocalMonitor)) {
			return false;
		}
		value = pLocalMonitor->valuedouble;
		return true;
	}

	bool CppJson::Get(const std::string& key, float& value)
	{
		double d_value = 0.0f;
		bool ret = Get(key, d_value);
		value = static_cast<double>(d_value);
		return ret;
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

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) != NULL) {
			return false;
		}
		cJSON* pJsonStruct = ::cJSON_CreateString(value.c_str());
		if (pJsonStruct == nullptr) {
			return false;
		}
		if (!::cJSON_AddItemToObject(pLocalMonitor, key.c_str(), pJsonStruct)) {
			return false;
		}

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) == NULL) {
			return false;
		}

		return true;
	}

	bool CppJson::Add(const std::string& key, const int& value)
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

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) != NULL) {
			return false;
		}
		cJSON* pJsonStruct = ::cJSON_CreateNumber(value);
		if (pJsonStruct == nullptr) {
			return false;
		}
		if (!::cJSON_AddItemToObject(pLocalMonitor, key.c_str(), pJsonStruct)) {
			return false;
		}

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) == NULL) {
			return false;
		}

		return true;
	}

	bool CppJson::Add(const std::string& key, const double& value)
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

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) != NULL) {
			return false;
		}
		cJSON* pJsonStruct = ::cJSON_CreateNumber(value);
		if (pJsonStruct == nullptr) {
			return false;
		}
		if (!::cJSON_AddItemToObject(pLocalMonitor, key.c_str(), pJsonStruct)) {
			return false;
		}

		if (::cJSON_GetObjectItem(pLocalMonitor, key.c_str()) == NULL) {
			return false;
		}

		return true;
	}

	bool CppJson::Add(const std::string& key, const float& value)
	{
		return Add(key, (double)value);
	}

	cJSON* CppJson::_get_valid_object()
	{
		if (_pmonitor == nullptr) {
			_pmonitor = ::cJSON_CreateObject();
			return _pmonitor;
		}
		else {
			return _pmonitor;
		}
		return nullptr;
	}
}