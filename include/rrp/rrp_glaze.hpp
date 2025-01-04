#pragma once


#include "reflect"
#include "rrp/rrp.hpp"
#include <concepts>
#include <glaze/core/opts.hpp>
#include <glaze/json/json_t.hpp>
#include <glaze/json/write.hpp>
#include <string_view>

#if !(__has_include(<glaze/glaze.hpp>))

#error Glaze not found
#endif

#include <glaze/glaze.hpp>

struct IndexedValueWIndexMember
{
   glz::json_t value{};
   int index;

   bool operator<(const auto& rhs) {
      return index < rhs.index;
   }
};

template<> struct glz::meta<IndexedValueWIndexMember> {
   static constexpr auto value{ &IndexedValueWIndexMember::value };
};


namespace glz::detail
{

std::vector<json_t> delimBaseConverter(const auto& v)
{
   std::cout << "NORMAL: ";
   for(auto& a : v)
   {
      std::cout << a << ",";
   }
   std::cout << "\n";
   std::vector<json_t> ret;
   std::copy(v.begin(), v.end(), std::back_inserter(ret));

   return ret;
}


template <class T>
   requires std::derived_from<T, ::rrp::ValueMapContainer>
struct to<JSON, T> {
   template <auto Opts>
   static void op(const T& type, auto&&... args) noexcept {
      std::vector<std::pair<std::string, IndexedValueWIndexMember>> map;
      
      ::reflect::for_each([&](auto I){
         std::string_view name = ::reflect::member_name<I>(type);
         if(name.substr(0, 2) == "m_") name = name.substr(2);
         using M = std::remove_reference_t<decltype(::reflect::get<I>(type))>;
         using V = decltype(M::value);
         int key = M::KEY;

         if constexpr(std::derived_from<V, rrp::DelimBasedContainerBase>)
         {
            map.emplace_back(std::string{name},
               IndexedValueWIndexMember{
                  .value = delimBaseConverter(::reflect::get<I>(type).value.values),
                  .index = key
               }
            );
         }
         else
         {
            map.emplace_back( std::string{name},
               IndexedValueWIndexMember{
                  .value = ::reflect::get<I>(type).value,
                  .index = key
               }
            );
         }

   }, type);

      std::sort(map.begin(), map.end(), [](const auto& l, const auto& r){
         return l.second.index < r.second.index;
      });
      write<JSON>::op<Opts>(map, args...);
   }
};



template <class T>
   requires std::derived_from<T, ::rrp::SimpleDelimSeparatedBase>
struct to<JSON, T> {
   template <auto Opts>
   static void op(const T& type, auto&&... args) noexcept {
      glz::json_t::object_t map;
      ::reflect::for_each([&](auto I){
         std::string_view name = ::reflect::member_name<I>(type);
         if(name.substr(0, 2) == "m_") name = name.substr(2);
         map.emplace(name, ::reflect::get<I>(type));
      }, type);
      write<JSON>::op<Opts>(map, args...);
   }
};

}  // namespace glz::detail



template <typename T, int index>
struct glz::meta<::rrp::IndexedValueMap<T, index>> {
   static constexpr auto value{ &rrp::IndexedValueMap<T, index>::value };
};

template<typename T, reflect::fixed_string D>
struct glz::meta<rrp::DelimBasedContainer<T, D>> {
   static constexpr auto value { &rrp::DelimBasedContainer<T, D>::values };
};


