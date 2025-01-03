#pragma once


#include "reflect"
#include "rrp/rrp.hpp"
#include <glaze/core/opts.hpp>
#include <glaze/json/write.hpp>
#if !(__has_include(<glaze/glaze.hpp>))

#error Glaze not found
#endif

#include "rrp/2.2/common.hpp"
#include <glaze/glaze.hpp>

/*
struct BaseSpecifier {};

struct MyValue : public BaseSpecifier
{
    int something;
};

template <class T> requires std::derived_from<T, BaseSpecifier>
struct glz::meta<T>
{
   static constexpr auto custom_write = true;
};

namespace glz::detail
{
    template <class T> requires std::derived_from<T, BaseSpecifier>
    struct to<JSON, T>
   {
      template <auto Opts>
      static void op(const T& map, auto&&... args) noexcept
      {
        write<JSON>::op<Opts>("test", args...);
      }
   };
}

*/

template <typename T, int index>
struct glz::meta<rrp::IndexedValueMap<T, index>> {
  static constexpr auto value{ &rrp::IndexedValueMap<T, index>::value };
};


namespace glz::detail
{
   template <>
   struct to<JSON, rrp::v22::LevelObject>
   {
      template <auto Opts>
      static void op(const rrp::v22::LevelObject& level, auto&&... args) noexcept
      {
        glz::json_t::object_t obj;
        ::reflect::for_each([&](auto I){
            obj.insert({std::string(::reflect::member_name<I>(level)), ::reflect::get<I>(level).value});
        }, level);
        write<JSON>::op<Opts>(obj, args...);
      }
   };
}