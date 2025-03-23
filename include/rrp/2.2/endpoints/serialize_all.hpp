#pragma once

#include "all.hpp"

#include <rrp/rrp_serialize.hpp>
#include "enum.hpp"
#include "rrp/2.2/endpoints/downloadGJLevel22.hpp"

namespace rrp::v22
{

template<typename T>
inline std::optional<std::string> json_from_response(std::string_view response, int dump = 4)
{
    if(auto r = rrp<T>(response))
        return write_json(*r).dump(dump);
    return {};
}

inline std::optional<std::string> rrp_json(std::string_view response, v22::Endpoint endpoint, int dump = 4)
{
    switch (endpoint)
    {
        case Endpoint::DownloadGJLevel22: return json_from_response<downloadGJLevel22>(response);
        case Endpoint::GetGJAccountComments20: return json_from_response<getGJAccountComments20>(response);
        case Endpoint::GetGJComments21: return json_from_response<getGJComments21>(response);
        case Endpoint::GetGJDailyLevel: return json_from_response<getGJDailyLevel>(response);
        case Endpoint::GetGJGauntlets21: return json_from_response<getGJGauntlets21>(response);
        case Endpoint::GetGJLevelLists: return json_from_response<getGJLevelLists>(response);
        case Endpoint::GetGJLevels21: return json_from_response<getGJLevels21>(response);
        case Endpoint::GetGJMapPacks21: return json_from_response<getGJMapPacks21>(response);
        case Endpoint::GetGJMessages20: return json_from_response<getGJMessages20>(response);
        case Endpoint::GetGJRewards: return json_from_response<getGJRewards>(response);
        case Endpoint::GetGJScores20: return json_from_response<getGJScores20>(response);
        case Endpoint::GetGJSongInfo: return json_from_response<getGJSongInfo>(response);
        case Endpoint::GetGJUserInfo20: return json_from_response<getGJUserInfo20>(response);
        case Endpoint::GetGJUsers20: return json_from_response<getGJUsers20>(response);
        case Endpoint::UploadGJLevel21: return json_from_response<uploadGJLevel21>(response);
    }    

    return {};
}

inline std::optional<std::string> rpp_json(std::string_view response, std::string_view url, int dump = 4)
{
    std::optional<std::string> ret;
    isEndpointSupportedWithType(url, [&]<typename T>(){
        ret = json_from_response<T>(response);
    });
    return ret;
}


}

