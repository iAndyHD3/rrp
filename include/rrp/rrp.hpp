#pragma once

#include "reflect"
#include <type_traits>
#include "fast_float.h"

#ifndef RRP_STRING_TYPE
#include <string>
#define RRP_STRING_TYPE std::string
#endif

#include "static_string/static_string.h"

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
constexpr T fromString(rrp::string_view str)
{
	if constexpr (std::is_same_v<T, bool>)
	{
		return str == "1" || str == "true";
	}
	else
	{
		T value;
		if constexpr (fast_float::from_chars(str.data(), str.data() + str.size(), value).ec == std::errc())
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


template<typename T>
constexpr Response rrp(std::string_view str)
{
    if constexpr(T::DELIM.empty())
    {
        return {};
    }

    Response r;

    constexpr auto splitted = splitByDelimStringView(str, T::DELIM);

    auto it = splitted.begin();

    reflect::for_each([&](auto I)
    {
        reflect::get<I>(r) = fromString<std::remove_reference_t<decltype(reflect::get<I>(r))>>(*it);
        ++it;
    }, r);

    return r;
}


template<cts::static_string str, cts::static_string delim>
constexpr inline rrp::vector<rrp::string_view> splitByDelimStringView()
{
	constexpr rrp::vector<rrp::string_view> tokens;
	size_t pos = 0;
	size_t len = str.length();

	while (pos < len)
	{
		constexpr size_t end = str.find(delim, pos);
		if constexpr(end == std::string_view::npos)
		{
			tokens.emplace_back(strsubstr(pos));
			break;
		}
		tokens.emplace_back(str.substr(pos, end - pos));
		pos = end + delim.size();
	}

	return tokens;
}

constexpr std::size_t upper_bound_for_make_vector(const auto str, const auto delim)
{
    std::size_t count = 1;
    std::size_t pos = 0;

    pos = str.template find<0, delim.m_elems>(delim);
    while (pos != std::string_view::npos) {
        ++count;
        pos = str.template find<pos + delim.size()>(delim);
    }

    return count;
}


constexpr inline auto splitByDelimStringViewArray(auto str, auto delim)
{
    const auto vec = splitByDelimStringView<str, delim>();
    std::array<std::string_view, upper_bound_for_make_vector<str, delim>()> tokens; 
    tokens[0] = vec[0];


    return tokens;
    
}

constexpr void test()
{
    constexpr cts::static_string a = "1,2,3";
    constexpr cts::static_string b = ",";

    auto c = upper_bound_for_make_vector(a, b);

    constexpr auto x = splitByDelimStringViewArray<"1,2,3", ",">();

    static_assert(std::get<0>(x) == rrp::string_view{"1"});


}

}