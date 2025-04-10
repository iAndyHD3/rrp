#pragma once

#include "reflect"
#include "rrp/rrp.hpp"
#include "rrp/base64.h"
#include <concepts>
#include <string_view>
#include <type_traits>

#include <matjson.hpp>
#include <matjson/std.hpp>
#include <utility>

struct IndexedValueWIndexMember
{
    matjson::Value value{};
    std::string name;
    int index;

    bool operator<(const auto& rhs)
    {
        return index < rhs.index;
    }
};

namespace rrp
{

inline std::string fix_key_name(std::string_view name)
{
    if(name.ends_with("auto_")) return "auto";
    if(name.starts_with("m_")) return std::string(name.substr(2));
    return std::string(name);
}


template<typename T> requires std::is_enum_v<T>
matjson::Value write_json(T& t)
{
    return matjson::Value(std::to_underlying(t));
}

template <typename R> requires std::is_aggregate_v<R>
matjson::Value write_json(R& t)
{
    using T = std::remove_reference_t<R>;

    if constexpr (std::is_enum_v<T>)
    {
        return std::to_underlying(t);
    }
    else if constexpr (std::derived_from<T, rrp::ValueMapContainer>)
    {
        auto globret = matjson::Value::object();
        std::vector<IndexedValueWIndexMember> orderVec;
        reflect::for_each(
            [&](auto I) {
                using M = std::remove_reference_t<decltype(reflect::get<I>(t))>;
                auto&& member = reflect::get<I>(t);
                auto&& name = reflect::member_name<I>(t);

                auto getValue = [&]() {
                    if constexpr (std::derived_from<M, IndexedValueBase64>)
                        return ::rrp::base64::decode(member.value);
                    else if constexpr(std::derived_from<M, IndexedValueXoredBase64Base>)
                        return xor_cycle(::rrp::base64::decode(member.value), M::XOR_KEY);
                    else if constexpr (std::is_convertible_v<decltype(M::value), matjson::Value>)
                        return member.value;
                    //else if constexpr (std::derived_from<M, IndexedValueXorBase>)
                    //    return xor_cycle(member.value, M::XOR_KEY);
                    else
                        return write_json(member.value);
                };

                orderVec.emplace_back(
                    IndexedValueWIndexMember{.value = getValue(), .name = fix_key_name(name), .index = M::KEY});
            },
            t);

        std::sort(orderVec.begin(), orderVec.end(), [](const auto& l, const auto& r) { return l.index < r.index; });
        for (const auto& o : orderVec)
        {
            globret.set(o.name, o.value);
        }
        return globret;
    }
    else if constexpr (std::derived_from<T, DelimBasedContainerBase>)
    {
        auto ret = matjson::Value::array();
        if constexpr (std::derived_from<typename T::type, ValueMapContainer> ||
                      std::derived_from<typename T::type, SimpleDelimSeparatedBase>)
        {
            for (const auto& valuemaps : t.values)
            {
                ret.push(write_json(valuemaps));
            }
        }
        else if constexpr (std::is_convertible_v<typename T::type, matjson::Value>)
        {
            for (const auto& valuemaps : t.values)
            {
                ret.push(valuemaps);
            }
        }

        return ret;
    }

    /*from indexed value map*/
    else if constexpr (std::derived_from<T, IndexedValueBase>)
    {
        return write_json(t.value);
    }
    else
    {
        auto ret = matjson::Value::object();
        reflect::for_each(
            [&](auto I) {
                using M = std::remove_reference_t<decltype(reflect::get<I>(t))>;
                auto&& member = reflect::get<I>(t);
                auto&& name = reflect::member_name<I>(t);

                if constexpr (std::is_convertible_v<M, matjson::Value>)
                {
                    ret.set(fix_key_name(name), member);
                }
                else
                {
                    ret.set(fix_key_name(name), write_json(member));
                }
            },
            t);

        return ret;
    }
}


} // namespace rrp