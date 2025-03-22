#include <unordered_map>
#include <vector>
#include <string_view>
#include <rrp/fromString.hpp>

namespace rrp
{

std::vector<std::string_view> splitByDelimStringView(std::string_view str, std::string_view delim)
{
	std::vector<std::string_view> tokens;
	size_t pos = 0;
	size_t len = str.length();

	while (pos < len)
	{
		size_t end = str.find(delim, pos);
		if (end == std::string_view::npos)
		{
			tokens.emplace_back(str.substr(pos));
			break;
		}
		tokens.emplace_back(str.substr(pos, end - pos));
		pos = end + delim.length();
	}

	return tokens;
}

std::unordered_map<int, std::string_view> splitByDelimToMap(std::string_view str, std::string_view delim)
{
    std::unordered_map<int, std::string_view> tokens;
    size_t pos = 0;
    size_t len = str.length();

    while (pos < len)
    {
        // Find the position of the delimiter for the key
        size_t key_end = str.find(delim, pos);
        if (key_end == std::string_view::npos) break; // No more delimiters found, end of string

        // Extract the key
        std::string_view key = str.substr(pos, key_end - pos);
        pos = key_end + delim.length(); // Move past the delimiter

        // Find the position of the delimiter for the value
        size_t value_end = str.find(delim, pos);
        if (value_end == std::string_view::npos) {
            // If no delimiter found for value, it means value is until the end of string
            std::string_view value = str.substr(pos);
            if (auto k = fromString<int>(key)) tokens.emplace(*k, value);
            break;
        }

        // Extract the value
        std::string_view value = str.substr(pos, value_end - pos);
        pos = value_end + delim.length(); // Move past the delimiter

        // Insert into map if key can be converted to int
        if (auto k = fromString<int>(key)) tokens.emplace(*k, value);
    }

    return tokens;
}

}
