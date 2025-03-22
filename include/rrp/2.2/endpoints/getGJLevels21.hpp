#pragma once
#include <rrp/2.2/PageInfo.hpp>
#include <rrp/2.2/LevelObject.hpp>
#include <rrp/2.2/CreatorObject.hpp>
#include <rrp/2.2/SongObject.hpp>

namespace rrp::v22
{
struct getGJLevels21
{

    RRP_DELIM("#");
    RRP_DBC_W_GETTER(rrp::v22::LevelObject, "|", levels);
    RRP_DBC_W_GETTER(rrp::v22::CreatorObject, "|", creators);
    RRP_DBC_W_GETTER(rrp::v22::SongObject, "~:~", songs);

    rrp::v22::PageInfo pageInfo;
    std::string hash;
};
}
