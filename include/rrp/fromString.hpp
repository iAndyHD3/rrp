#include "fast_float.h"

#include <string_view>
#include <optional>
#include <type_traits>
#include <utility>

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
            return std::optional<T>(std::in_place, static_cast<T>(*val));
        }
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        return std::optional<std::string>(std::in_place, str);
    }
    else if constexpr (std::is_same_v<T, std::string_view>)
    {
        return std::optional<T>(std::in_place, str);
    }

    else if constexpr (std::is_same_v<T, bool>)
	{
		return std::optional<T>(std::in_place, str == "1" || str == "true");
	}
    else
	{
        std::optional<T> value(std::in_place);
		if (fast_float::from_chars(str.data(), str.data() + str.size(), *value).ec == std::errc())
		{
			return value;
		}
	}
	return {};
}