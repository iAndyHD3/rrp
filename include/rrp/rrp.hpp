#pragma once
#include <source_location>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>
#include "reflect"
#include <iostream>
#include "fast_float.h"
#include <optional>

namespace rrp
{

inline void myprint(auto a, std::source_location x = std::source_location::current())
{
    std::cout << a << " | " << x.file_name() << ":" << x.line() << '\n';
}

template<typename T>
std::optional<T> fromString(std::string_view str)
{
    if constexpr (std::is_same_v<T, std::string>)
    {
        return std::string(str);
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
inline std::vector<std::string_view> splitByDelimStringView(std::string_view str, std::string_view delim)
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
		pos = end + 1;
	}

	return tokens;
}

inline std::unordered_map<int, std::string_view> splitByDelimToMap(std::string_view str, std::string_view delim)
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


template<typename T, int index>
struct IndexedValueMap
{
    using type = T;
    T value{};
    operator T() { return value; }
    T* operator->() { return value; }
    auto operator<=>(const T& rhs) const {
        return value <=> rhs;
    }

    constexpr static int KEY = index;
    static auto parse(std::string_view str)
    {
        IndexedValueMap<T, index> ret;
        if(auto v = fromString<T>(str)) ret.value = *v;
        return ret;
    }
};


struct ValueMapContainer
{
    template<typename T>
    static T parse(std::string_view str)
    {
        myprint("\n");
        myprint(str);
        T ret;
        auto tokens = splitByDelimToMap(str, T::DELIM);
        myprint(tokens.size());
        for(const auto& k : tokens)
        {
            std::string x = std::to_string(k.first) + ":" + std::string(k.second);
            myprint(x);
        }
        reflect::for_each([&](auto I){
            using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
            auto&& member = reflect::get<I>(ret);
            if(auto value_it = tokens.find(M::KEY); value_it != tokens.end())
            {
                if(auto v2_parsed = fromString<typename M::type>(value_it->second))
                {
                    member.value = *v2_parsed;
                }
            }
        }, ret);
        return ret;
    }
};

#define RRP_IVM_W_GETTER(T, index, name) \
    IndexedValueMap<T, index> m_##name; \
    T& name() { return m_##name.value; }



// Define a concept that matches numerical types but excludes char
template <typename T>
concept is_numerical_generic = std::is_arithmetic_v<T> && !std::is_same_v<T, char>;

template <typename T>
concept has_non_empty_delim = requires {!T::DELIM.size() != 0;};



#define RRP_DBC_W_GETTER(T, delim, name) \
    DelimBasedContainer<T, delim> m_##name; \
    std::vector<T>& name() { return m_##name.values ;}



struct DelimBasedContainerBase {};
template<typename T, reflect::fixed_string D>
struct DelimBasedContainer : DelimBasedContainerBase
{
    static constexpr reflect::fixed_string DELIM = D;
    std::vector<T> values;
    operator std::vector<T>() { return values; }

    //level1,level2,
    //where level: 0:1:2:name:3:desc
    static auto parse(std::string_view str)
    {
        
        DelimBasedContainer<T, D> ret;
        if constexpr(has_non_empty_delim<T>)
        {
            myprint(str);
            auto tokens = splitByDelimStringView(str, DELIM);
            for(const auto& t : tokens)
            {
                ret.values.push_back(T::template parse<T>(t));
            }
        }
        return ret;
    }
};

template<typename T>
bool is_indexed_value_map_only()
{
    bool ret = true;
    reflect::for_each<T>([&](auto I){
        if (reflect::type_name(reflect::get<I>(std::declval<T>())) != "IndexedValueMap")
        {
            ret = false;
            return;
        }
    });

    return ret;
}



template<typename T>
T rrp(std::string_view str)
{
    T ret;
    auto tokens = splitByDelimStringView(str, T::DELIM);
    auto it = tokens.begin();
    reflect::for_each([&](auto I)
    {
        if(it == tokens.end()) return;

        using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
        auto&& member = reflect::get<I>(ret);
        auto&& member_name = reflect::type_name(member);
        if constexpr(std::is_base_of_v<DelimBasedContainerBase, M>)
        {
            std::cout << "HELLO";
            member = M::parse(*it);
            ++it;
        }
        else if constexpr(std::is_base_of_v<ValueMapContainer, M>)
        {
            member = M::template parse<M>(*it);
            ++it;
        }
    }, ret);

    return ret;
}



template<reflect::fixed_string D = "">
struct LevelObject : public ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = D;

    // Integer getters
    RRP_IVM_W_GETTER(int, 1, levelID);
    RRP_IVM_W_GETTER(int, 5, version);
    RRP_IVM_W_GETTER(int, 6, playerID);
    RRP_IVM_W_GETTER(int, 8, difficultyDenominator);
    RRP_IVM_W_GETTER(int, 9, difficultyNumerator);
    RRP_IVM_W_GETTER(int, 10, downloads);
    RRP_IVM_W_GETTER(int, 11, setCompletes); // Note: Removed in update 2.1
    RRP_IVM_W_GETTER(int, 12, officialSong);
    RRP_IVM_W_GETTER(int, 13, gameVersion);
    RRP_IVM_W_GETTER(int, 14, likes);
    RRP_IVM_W_GETTER(int, 15, length);
    RRP_IVM_W_GETTER(int, 16, dislikes);
    RRP_IVM_W_GETTER(int, 18, stars);
    RRP_IVM_W_GETTER(int, 19, featureScore);
    RRP_IVM_W_GETTER(int, 30, copiedID);
    RRP_IVM_W_GETTER(int, 35, customSongID);
    RRP_IVM_W_GETTER(int, 37, coins);
    RRP_IVM_W_GETTER(int, 39, starsRequested);
    RRP_IVM_W_GETTER(int, 41, dailyNumber); // Note: Specific to daily/weekly levels
    RRP_IVM_W_GETTER(int, 42, epic);
    RRP_IVM_W_GETTER(int, 43, demonDifficulty);
    RRP_IVM_W_GETTER(int, 45, objects);
    RRP_IVM_W_GETTER(int, 46, editorTime);
    RRP_IVM_W_GETTER(int, 47, editorTimeCopies);
    RRP_IVM_W_GETTER(int, 54, unknown);
    RRP_IVM_W_GETTER(int, 57, verificationTime);

    // Bool getters
    RRP_IVM_W_GETTER(bool, 17, demon);
    RRP_IVM_W_GETTER(bool, 25, auto_);
    RRP_IVM_W_GETTER(bool, 31, twoPlayer);
    RRP_IVM_W_GETTER(bool, 38, verifiedCoins);
    RRP_IVM_W_GETTER(bool, 40, lowDetailMode);
    RRP_IVM_W_GETTER(bool, 44, isGauntlet);

    // String getters
    RRP_IVM_W_GETTER(std::string, 2, levelName);
    RRP_IVM_W_GETTER(std::string, 3, description);
    RRP_IVM_W_GETTER(std::string, 4, levelString);
    RRP_IVM_W_GETTER(std::string, 26, recordString); // Note: Unused
    RRP_IVM_W_GETTER(std::string, 28, uploadDate);
    RRP_IVM_W_GETTER(std::string, 29, updateDate);
    RRP_IVM_W_GETTER(std::string, 36, extraString);
    RRP_IVM_W_GETTER(std::string, 48, settingsString); // Note: Unused after early 2.1

    // Encrypted String getters
    RRP_IVM_W_GETTER(std::string, 27, password);

    // Comma-Separated List getters
    RRP_IVM_W_GETTER(std::string, 52, songIDs);
    RRP_IVM_W_GETTER(std::string, 53, sfxIDs);
};

template<reflect::fixed_string D>
struct CreatorObject
{
    static reflect::fixed_string DELIM = D;
    //TODO simple comma separated values 
};

struct GJLevels21
{
    static constexpr reflect::fixed_string DELIM = "#";
    RRP_DBC_W_GETTER(LevelObject<":">, "|", levels);
};

}