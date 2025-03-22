#pragma once
#include <rrp/rrp.hpp>

namespace rrp::v22
{
struct SongObject : rrp::ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = "~|~";
    RRP_IVM_W_GETTER(int, 1, songID);
    RRP_IVM_W_GETTER(int, 3, artistID);
    RRP_IVM_W_GETTER(float, 5, sizeInMB);
    RRP_IVM_W_GETTER(int, 9, songPriority);
    RRP_IVM_W_GETTER(int, 11, nongEnum);
    RRP_IVM_W_GETTER(int, 14, newType);

    RRP_IVM_W_GETTER(std::string_view, 2, name);
    RRP_IVM_W_GETTER(std::string_view, 4, artistName);
    RRP_IVM_W_GETTER(std::string_view, 6, videoID);
    RRP_IVM_W_GETTER(std::string_view, 7, artistYTURL);
    RRP_IVM_W_GETTER(std::string_view, 10, downloadLink);
    //TODO parse this (simple delim container)

    RRP_IVM_DBC_W_GETTER(int, 12, ".", extraArtistsIDs)
    RRP_IVM_W_GETTER(std::string_view, 15, extraArstistNames);

    RRP_IVM_W_GETTER(bool, 8, isArtistScouted);
    RRP_IVM_W_GETTER(bool, 13, isNew);

};

}