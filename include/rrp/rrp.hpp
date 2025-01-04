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
concept Parsable = requires(T t, std::string_view str) {
    // Check if T::parse<T>(str) is valid where parse returns T
    { T::template parse<T>(str) } -> std::same_as<T>;
};

template<typename T>
concept BasicTypeOrString = std::integral<T> || std::floating_point<T> || std::same_as<T, bool> || 
                            std::same_as<T, std::string> || std::same_as<T, std::string_view>;

template<BasicTypeOrString T>
std::optional<T> fromString(std::string_view str)
{
    if constexpr (std::is_same_v<T, std::string>)
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

    constexpr static int KEY = index;
    static auto parse(std::string_view str)
    {
        IndexedValueMap<T, index> ret;
        if constexpr(Parsable<T>)
        {
            ret.value = T::template parse<T>(str);
        }
        else if(auto v = fromString<T>(str)) ret.value = *v;
        return ret;
    }
};


struct ValueMapContainer
{
    static constexpr auto glaze_reflect = false;
    template<typename T>
    static T parse(std::string_view str)
    {
        //myprint("\n");
        //myprint(str);
        T ret;
        auto tokens = splitByDelimToMap(str, T::DELIM);
        //myprint(tokens.size());
        //for(const auto& k : tokens)
        //{
        //    std::string x = std::to_string(k.first) + ":" + std::string(k.second);
        //    myprint(x);
        //}
        reflect::for_each([&](auto I){
            using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
            auto&& member = reflect::get<I>(ret);
            if(auto value_it = tokens.find(M::KEY); value_it != tokens.end())
            {
                member = M::parse(value_it->second);
            }
        }, ret);
        return ret;
    }
};

#define RRP_IVM_W_GETTER(T, index, name) \
    rrp::IndexedValueMap<T, index> m_##name; \
    T& name() { return m_##name.value; }



// Define a concept that matches numerical types but excludes char
template <typename T>
concept is_numerical_generic = std::is_arithmetic_v<T> && !std::is_same_v<T, char>;

template <typename T>
concept has_non_empty_delim = requires {!T::DELIM.size() != 0;};



#define RRP_DBC_W_GETTER(T, delim, name) \
    rrp::DelimBasedContainer<T, delim> m_##name; \
    std::vector<T>& name() { return m_##name.values ;}

#define RRP_DELIM(D) static constexpr reflect::fixed_string DELIM = D

struct DelimBasedContainerBase
{
    static constexpr auto glaze_reflect = false;
};

template<typename T, reflect::fixed_string D>
struct DelimBasedContainer : DelimBasedContainerBase
{
    using value = T;
    static constexpr reflect::fixed_string DELIM = D;
    std::vector<T> values;
    operator std::vector<T>() { return values; }

    //level1,level2,
    //where level: 0:1:2:name:3:desc
    template<typename U>
    static auto parse(std::string_view str)
    {
        
        U ret;
        auto tokens = splitByDelimStringView(str, U::DELIM);
        if constexpr(Parsable<T>)
        {
            for(const auto& t : tokens) ret.values.push_back(T::template parse<T>(t));
        }
        else
        {
            for(const auto& t : tokens) if(auto v = fromString<T>(t)) ret.values.push_back(*v);
        }
        
        return ret;
    }
};



struct SimpleDelimSeparatedBase
{
    static constexpr auto glaze_reflect = false;

    template<typename T>
    static T parse(std::string_view str)
    {
        T ret;
        auto tokens = splitByDelimStringView(str, T::DELIM);
        reflect::for_each([&](auto I){
            auto&& member = reflect::get<I>(ret);
            using M = std::remove_reference_t<decltype(member)>;
            if constexpr(Parsable<M>)
            {
                member = M::template parse<M>(tokens[I]);
            }
            else if(auto opt = fromString<M>(tokens[I]))
            {
                member = *opt;
            }
        }, ret);

        return ret;
    }
};




template<typename T>
T rrp(std::string_view str)
{
    T ret;
    if constexpr(Parsable<T>)
    {
        return T::template parse<T>(str);
    }
    else if constexpr(reflect::size<T>() == 1)
    {
        using M = std::remove_reference_t<decltype(reflect::get<0>(ret))>;
        reflect::get<0>(ret) = rrp::rrp<M>(str);
        return ret;
    }


    auto tokens = splitByDelimStringView(str, T::DELIM);
    auto it = tokens.begin();
    reflect::for_each([&](auto I)
    {
        if(it == tokens.end()) return;

        using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
        auto&& member = reflect::get<I>(ret);
        //myprint(reflect::type_name<M>());
        if constexpr(Parsable<M>)
        {
            member = M::template parse<M>(*it);
            ++it;
        }
        else if constexpr(BasicTypeOrString<M>)
        {
            if(auto v = fromString<M>(*it))
            {
                member = *v;
            }
            ++it;
        }
    }, ret);

    return ret;
}






//TODO

/*
struct UserObject {};
template<reflect::fixed_string D>
struct GetGJScores20
{
    
    std::vector<UserObject> objects;
};
*/
}