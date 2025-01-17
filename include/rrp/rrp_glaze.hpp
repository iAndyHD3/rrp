#pragma once


#include "reflect"
#include "rrp/rrp.hpp"
#include <concepts>
#include <string_view>
#include <type_traits>

#if !(__has_include(<matjson.hpp>))

#error matjson not found
#endif

#include <matjson.hpp>
#include <matjson/std.hpp>

struct IndexedValueWIndexMember
{
   matjson::Value value{};
   std::string name;
   int index;

   bool operator<(const auto& rhs) {
      return index < rhs.index;
   }
};

namespace rrp
{

inline std::string fix_key_name(std::string_view name)
{
   if(name.substr(0, 2) != "m_") return std::string(name);
   return std::string(name.substr(2));
}


template<typename R>
matjson::Value write_json(R&& t)
{
   using T = std::remove_reference_t<R>;
   if constexpr(std::derived_from<T, rrp::ValueMapContainer>)
   {
      auto globret = matjson::Value::object();
      std::vector<IndexedValueWIndexMember> orderVec;
      reflect::for_each([&](auto I){
         using M = std::remove_reference_t<decltype(reflect::get<I>(t))>;
         auto&& member = reflect::get<I>(t);
         auto&& name = reflect::member_name<I>(t);
         if constexpr(std::is_convertible_v<decltype(M::value), matjson::Value>)
         {
            orderVec.emplace_back(IndexedValueWIndexMember{.value = member.value, .name = fix_key_name(name), .index = M::KEY});
         }
         else
         {
            orderVec.emplace_back(IndexedValueWIndexMember{.value = write_json(member), .name = fix_key_name(name), .index = M::KEY});
         }
      }, t);
      std::sort(orderVec.begin(), orderVec.end(), [](const auto& l, const auto& r){ return l.index < r.index; });
      for(const auto& o : orderVec)
      {
         globret.set(o.name, o.value);
      }
      return globret;
   }
   else if constexpr(std::derived_from<T, DelimBasedContainerBase>)
   {
      auto ret = matjson::Value::array();
      if constexpr(std::derived_from<typename T::type, ValueMapContainer> || std::derived_from<typename T::type, SimpleDelimSeparatedBase>)
      {
         for(const auto& valuemaps : t.values)
         {
            ret.push(write_json(valuemaps));
         }
      }
      else if constexpr(std::is_convertible_v<typename T::type, matjson::Value>)
      {
         for(const auto& valuemaps : t.values)
         {
            ret.push(valuemaps);
         }
      }

      return ret;
   }
   else if constexpr(std::derived_from<T, IndexedValueBase>)
   {
      return write_json(t.value);
   }
   else
   {
      auto ret = matjson::Value::object();
      reflect::for_each([&](auto I){
         using M = std::remove_reference_t<decltype(reflect::get<I>(t))>;
         auto&& member = reflect::get<I>(t);
         auto&& name = reflect::member_name<I>(t);


         if constexpr(std::is_convertible_v<M, matjson::Value>)
         {
            ret.set(fix_key_name(name), member);
         }
         else
         {
            ret.set(fix_key_name(name), write_json(member));
         }
      }, t);

      return ret;
   }
}

}