#include "downloadGJLevel22.hpp"
#include "downloadGJMessage20.hpp"
#include "getGJAccountComments20.hpp"
#include "getGJComments21.hpp"
#include "getGJDailyLevel.hpp"
#include "getGJGauntlets21.hpp"
#include "getGJLevelLists.hpp"
#include "getGJLevels21.hpp"
#include "getGJMapPacks21.hpp"
#include "getGJMessages20.hpp"
#include "getGJRewards.hpp"
#include "getGJScores20.hpp"
#include "getGJSongInfo.hpp"
#include "getGJUserInfo20.hpp"
#include "getGJUsers20.hpp"
#include "uploadGJLevel21.hpp"


namespace rrp::v22
{


template<typename F>
constexpr inline void forAllRequestTypes(F&& f)
{
    f.template operator()<downloadGJLevel22>();
    f.template operator()<downloadGJMessage20>();
    f.template operator()<getGJAccountComments20>();
    f.template operator()<getGJComments21>();
    f.template operator()<getGJDailyLevel>();
    f.template operator()<getGJGauntlets21>();
    f.template operator()<getGJLevelLists>();
    f.template operator()<getGJLevels21>();
    f.template operator()<getGJMapPacks21>();
    f.template operator()<getGJMessages20>();
    f.template operator()<getGJRewards>();
    f.template operator()<getGJScores20>();
    f.template operator()<getGJSongInfo>();
    f.template operator()<getGJUserInfo20>();
    f.template operator()<getGJUsers20>();
    f.template operator()<uploadGJLevel21>();
}

template<typename T>
constexpr inline bool stringContainsType(std::string_view url)
{
    return url.contains(reflect::type_name<T>());
}


constexpr inline bool isEndpointSupported(std::string_view url)
{
    bool ret = false;
    forAllRequestTypes([&]<typename T>()
    {
        if(ret) return;
        ret = stringContainsType<T>(url);
    });
    return ret;
}


constexpr inline void isEndpointSupportedWithType(std::string_view url, auto&& F)
{
    forAllRequestTypes([&]<typename T>()
    {
        if(stringContainsType<T>(url))
        {
            F.template operator()<T>();
            return;
        }
    });
}


}