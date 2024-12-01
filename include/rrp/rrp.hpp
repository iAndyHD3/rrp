#pragma once

#include "reflect"
#include <exception>
#include <type_traits>
#include "fast_float.h"
#include <concepts>
#include <iostream>

#ifndef RRP_STRING_TYPE
#include <string>
#define RRP_STRING_TYPE std::string
#endif


#ifndef RRP_STRING_VIEW_TYPE
#include <string_view>
#define RRP_STRING_VIEW_TYPE std::string_view
#endif


#ifndef RRP_VECTOR_TYPE
#include <vector>
#define RRP_VECTOR_TYPE std::vector
#endif


#ifndef RRP_OPTIONAL_TYPE
#include <optional>
#define RRP_OPTIONAL_TYPE std::optional
#endif


namespace rrp
{

template<typename T>
using vector = RRP_VECTOR_TYPE<T>;

template<typename T>
using optional = RRP_OPTIONAL_TYPE<T>;

using string = RRP_STRING_TYPE;
using string_view = RRP_STRING_VIEW_TYPE;


template<typename T>
rrp::optional<T> fromString(rrp::string_view str)
{
	if constexpr (std::is_same_v<T, bool>)
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


struct Response
{
    int a;
    int b;
    int c;
    static constexpr rrp::string_view DELIM = ",";
};


// Define a concept that matches numerical types but excludes char
inline rrp::vector<rrp::string_view> splitByDelimStringView(std::string_view str, std::string_view delim)
{

	rrp::vector<rrp::string_view> tokens;
	size_t pos = 0;
	size_t len = str.length();

	while (pos < len)
	{
		size_t end = str.find(delim, pos);
		if(end == std::string_view::npos)
		{
			tokens.emplace_back(str.substr(pos));
			break;
		}
		tokens.emplace_back(str.substr(pos, end - pos));
		pos = end + delim.size();
	}

	return tokens;
}

// Define a concept that matches numerical types but excludes char
template <typename T>
concept is_numerical_generic = std::is_arithmetic_v<T> && !std::is_same_v<T, char>;

template <typename T>
concept has_non_empty_delim = requires {
    { T::DELIM } -> std::convertible_to<std::string_view>;
} && (!T::DELIM.empty());


template<typename T>
concept other = std::constructible_from<T, rrp::string_view>;


template<typename T>
T rrp(std::string_view str)
{
    static_assert(has_non_empty_delim<T>, "Type needs to have a non empty static constexpr std::string_view DELIM member");

    if constexpr(T::DELIM.empty())
    {
        return {};
    }

    T r;

    auto splitted = splitByDelimStringView(str, T::DELIM);

    auto it = splitted.begin();

    reflect::for_each([&](auto I)
    {
        using MemberType = std::remove_reference_t<decltype(reflect::get<I>(r))>;
        if constexpr(is_numerical_generic<MemberType>)
        {
            auto opt = fromString<MemberType>(*it);
            if(opt) reflect::get<I>(r) = *opt;
        }
        else if constexpr(has_non_empty_delim<MemberType>)
        {
            reflect::get<I>(r) = rrp<MemberType>(*it);
        }
        else if constexpr(std::constructible_from<MemberType, rrp::string_view>)
        {
            reflect::get<I>(r) = MemberType(*it);
        }

        ++it;
        
    }, r);

    return r;
}



}