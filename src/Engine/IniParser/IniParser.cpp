#include "IniParser.hpp"

#include <SimpleIni.h>
#include "../Debug/Debug.hpp"


std::shared_mutex le::IniParser::m_mutex;

std::unordered_map<std::string, le::IniParser::IniValues> le::IniParser::m_iniChache;


std::string le::IniParser::getValue(const std::string& path, const std::string& valuePath)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);

	if (path.empty() || valuePath.empty())
		LOG_WARN("Path or value path is empty.");


	if (m_iniChache.find(path) != m_iniChache.end())
	{
		LOG_DEBUG("Value found in chache file: " + path + " for key: " + valuePath + " with value: " + m_iniChache[path][valuePath]);

		return m_iniChache[path][valuePath];
	}

	CSimpleIniA iniFile;

	SI_Error rc = iniFile.LoadFile(path.c_str());

	if (rc < 0)
		LOG_ERROR("Failed to load INI file: " + path + " with error code: " + std::to_string(rc));


	std::unordered_map<std::string, std::string> values;

	CSimpleIniA::TNamesDepend sections;

	iniFile.GetAllSections(sections);


	for (const auto& section : sections)
	{
		CSimpleIniA::TNamesDepend keys;

		iniFile.GetAllKeys(section.pItem, keys);

		for (const auto& key : keys)
		{
			const char* val = iniFile.GetValue(section.pItem, key.pItem, "");

			std::string fullKey = std::string(section.pItem) + "." + std::string(key.pItem);

			values[fullKey] = val;
		}
	}

	m_iniChache[path] = std::move(values);

	if (m_iniChache[path].find(valuePath) != m_iniChache[path].end())
	{
		LOG_DEBUG("Value found in INI file: " + path + " for key: " + valuePath + " with value: " + m_iniChache[path][valuePath]);

		return m_iniChache[path][valuePath];
	}


	LOG_ERROR("Value not found in INI file: " + path + " for key: " + valuePath);

	return "";
}
