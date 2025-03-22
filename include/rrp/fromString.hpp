#include "fast_float.h"

#include <string_view>
#include <optional>
#include <type_traits>

template<typename T>
concept BasicTypeOrString = std::integral<T> || std::floating_point<T> || std::same_as<T, bool> || 
                            std::same_as<T, std::string> || std::same_as<T, std::string_view> || std::is_enum_v<T>;

template<BasicTypeOrString T>
std::optional<T> fromString(std::string_view str)
{
    if constexpr (std::is_enum_v<T>)
    {
        if(auto val = fromString<std::underlying_type_t<T>>(str))
        {
            return static_cast<T>(*val);
        }
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        return std::string(str);
    }
    else if constexpr (std::is_same_v<T, std::string_view>)
    {
        return str;
    }

    else if constexpr (std::is_same_v<T, bool>)
	{
		return str == "1" || str == "true";
	}
    else
	{
		T value;
		if (fast_float::from_chars(str.data(), str.data() + str.size(), value).ec == std::errc())
		{
			return value;
		}
	}
	return {};
}