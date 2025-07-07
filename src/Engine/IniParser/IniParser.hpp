#pragma once
#include <shared_mutex>
#include "../Common.hpp"


namespace le
{
    #define INI_GET(type, path, key) le::IniParser::get<type>(path, key)


	class IniParser
	{
		static std::shared_mutex m_mutex;


		using IniValues = std::unordered_map<std::string, std::string>;

		static std::unordered_map<std::string, IniValues> m_iniChache;


		static std::string getValue(const std::string& path, const std::string& valuePath);

	public:

		template<typename T>
		static const T get(const std::string& path, const std::string& valuePath);
	};

	template<typename T>
	inline const T IniParser::get(const std::string& path, const std::string& valuePath)
	{
        if constexpr (std::is_same_v<T, std::string>)
        {
            return getValue(path, valuePath);
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return std::stoi(getValue(path, valuePath));
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            return std::stof(getValue(path, valuePath));
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return std::stod(getValue(path, valuePath));
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
			std::string value = getValue(path, valuePath);

            return value == "1" || value == "true" || value == "True";
        }
        else if constexpr (std::is_same_v<T, glm::vec2>)
        {
            glm::vec2 result;
            result.x = std::stof(getValue(path, valuePath + ".x"));
            result.y = std::stof(getValue(path, valuePath + ".y"));
            return result;
        }
        else if constexpr (std::is_same_v<T, glm::ivec2>)
        {
            glm::ivec2 result;
            result.x = std::stoi(getValue(path, valuePath + ".x"));
            result.y = std::stoi(getValue(path, valuePath + ".y"));
            return result;
        }
        else if constexpr (std::is_same_v<T, glm::vec3>)
        {
            glm::vec3 result;
            result.x = std::stof(getValue(path, valuePath + ".x"));
            result.y = std::stof(getValue(path, valuePath + ".y"));
            result.z = std::stof(getValue(path, valuePath + ".z"));
            return result;
        }
        else
        {
            static_assert(sizeof(T) == 0, "Unsupported type for IniParser::get");

			LOG_ERROR("Unsupported type for IniParser::get: " + std::string(typeid(T).name()));
        }
	}
}