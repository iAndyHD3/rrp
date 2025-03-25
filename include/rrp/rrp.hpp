#pragma once
#include <concepts>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <string_view>
#include "reflect"
#include "fast_float.h"
#include "fromString.hpp"
#include <iostream>

namespace rrp
{

inline void myprint(auto a, std::source_location x = std::source_location::current())
{
    std::cout << a << " | " << x.file_name() << ":" << x.line() << '\n';
}

template <typename T>
concept Parsable = requires(T t, std::string_view str) {
    // Check if T::parse<T>(str) is valid where parse returns T
    { T::template parse<T>(str) } -> std::same_as<T>;
};

template <typename T, typename B> struct AddTop : B {
    using top = T;
};

template <typename T> struct TreatAs : T {
    using treat_as = T;

};

std::vector<std::string_view> splitByDelimStringView(std::string_view str, std::string_view delim);
std::unordered_map<int, std::string_view> splitByDelimToMap(std::string_view str, std::string_view delim);

struct IndexedValueBase {};

// this is to correctly serialize the value...
struct IndexedValueBase64 {};

struct IndexedValueXorBase {};

struct IndexedValueXoredBase64Base {};

template<reflect::fixed_string KEY, typename B>
struct IndexedValueXored : B {
    static constexpr auto XOR_KEY = KEY;
};

template <typename T, int index, typename B = IndexedValueBase> struct IndexedValueMap : B {
    using type = T;
    T value{};

    constexpr static int KEY = index;
    static auto parse(std::string_view str)
    {
        IndexedValueMap<T, index, B> ret;
        if constexpr (Parsable<T>)
        {
            ret.value = T::template parse<T>(str);
        }
        else if (auto v = fromString<T>(str))
            ret.value = *v;
        return ret;
    }
};

#define RRP_IVM_W_GETTER(T, index, name)                                                                               \
    rrp::IndexedValueMap<T, index> m_##name;                                                                           \
    T& name()                                                                                                          \
    {                                                                                                                  \
        return m_##name.value;                                                                                         \
    }


struct ValueMapContainer {
    static constexpr auto glaze_reflect = false;
    template <typename T> static T parse(std::string_view str)
    {
        // myprint("\n");
        // myprint(str);
        T ret;
        auto tokens = splitByDelimToMap(str, T::DELIM);
        // myprint(tokens.size());
        // if constexpr(T::DELIM == "~|~")
        //{
        //     myprint(str);
        //     for(const auto& k : tokens)
        //     {
        //         std::string x = std::to_string(k.first) + ":" + std::string(k.second);
        //         myprint(x);
        //     }
        // }
        reflect::for_each(
            [&](auto I) {
                using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
                auto&& member = reflect::get<I>(ret);
                if (auto value_it = tokens.find(M::KEY); value_it != tokens.end())
                {
                    member = M::parse(value_it->second);
                }
            },
            ret);
        return ret;
    }
};

// Define a concept that matches numerical types but excludes char
template <typename T>
concept is_numerical_generic = std::is_arithmetic_v<T> && !std::is_same_v<T, char>;

template <typename T>
concept has_non_empty_delim = requires { !T::DELIM.size() != 0; };

#define RRP_DBC_W_GETTER(T, delim, name)                                                                               \
    rrp::DelimBasedContainer<T, delim> m_##name;                                                                       \
    std::vector<T>& name()                                                                                             \
    {                                                                                                                  \
        return m_##name.values;                                                                                        \
    }

#define RRP_DELIM(D) static constexpr reflect::fixed_string DELIM = D

struct DelimBasedContainerBase {};

template <typename T, reflect::fixed_string D> struct DelimBasedContainer : DelimBasedContainerBase {
    using type = T;
    static constexpr reflect::fixed_string DELIM = D;
    std::vector<T> values;
    operator std::vector<T>()
    {
        return values;
    }

    // level1,level2,
    // where level: 0:1:2:name:3:desc
    template <typename U> static auto parse(std::string_view str)
    {

        U ret;
        auto tokens = splitByDelimStringView(str, U::DELIM);
        if constexpr (Parsable<T>)
        {
            for (const auto& t : tokens)
                ret.values.push_back(T::template parse<T>(t));
        }
        else
        {
            for (const auto& t : tokens)
                if (auto v = fromString<T>(t))
                    ret.values.push_back(*v);
        }

        return ret;
    }
};


struct SimpleDelimSeparatedBase {
    static constexpr auto glaze_reflect = false;

    template <typename T> static T parse(std::string_view str)
    {
        T ret;
        auto tokens = splitByDelimStringView(str, T::DELIM);
        reflect::for_each(
            [&](auto I) {
                auto&& member = reflect::get<I>(ret);
                using M = std::remove_reference_t<decltype(member)>;
                if constexpr (Parsable<M>)
                {
                    member = M::template parse<M>(tokens[I]);
                }
                else if (auto opt = fromString<M>(tokens[I]))
                {
                    member = *opt;
                }
            },
            ret);

        return ret;
    }
};

// expects `value` to be a member of parent
struct SimpleIntResponseBase
{
    template <typename T> static T parse(std::string_view str)
    {
        T ret;
        if (auto val = fromString<std::int32_t>(str); *val > 0)
        {
            ret.value.emplace(*val);
        }
        return ret;
    }
};

template <typename T, typename = void> struct has_treat_as_alias : std::false_type {};

template <typename T> struct has_treat_as_alias<T, std::void_t<typename T::treat_as>> : std::true_type {};

template <typename T>
concept HasTreatAs = has_treat_as_alias<T>::value;


template <typename T> std::optional<T> rrp(std::string_view str)
{
    if (str == "-1")
        return {};

    T ret;

    if constexpr (Parsable<T>)
    {
        return T::template parse<T>(str);
    }

    // wrapper such that struct { int a; } is treated as that member
    else if constexpr (reflect::size<T>() == 1)
    {
        using M = std::remove_reference_t<decltype(reflect::get<0>(ret))>;

        reflect::get<0>(ret) = *rrp::rrp<M>(str);
        return ret;
    }
    else
    {
        auto tokens = splitByDelimStringView(str, T::DELIM);
        auto it = tokens.begin();
        reflect::for_each(
            [&](auto I) {
                if (it == tokens.end())
                    return;

                using M = std::remove_reference_t<decltype(reflect::get<I>(ret))>;
                auto&& member = reflect::get<I>(ret);
                // myprint(reflect::type_name<M>());
                if constexpr (Parsable<M>)
                {
                    member = M::template parse<M>(*it);
                    ++it;
                }
                else if constexpr (BasicTypeOrString<M>)
                {
                    if (auto v = fromString<M>(*it))
                    {
                        member = *v;
                    }
                    ++it;
                }
            },
            ret);

        return ret;
    }
}


#define RRP_IVM_DBC_W_GETTER(type, index, delim, name)                                                                 \
    rrp::IndexedValueMap<rrp::DelimBasedContainer<type, delim>, index> m_##name;                                       \
    std::vector<type> name()                                                                                           \
    {                                                                                                                  \
        return m_##name.value.values;                                                                                  \
    }

} // namespace rrp