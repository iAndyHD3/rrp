#pragma once
#include "common.hpp"

struct GetGJLevels21
{

    RRP_DELIM("#");
    RRP_DBC_W_GETTER(rrp::v22::LevelObject, "|", levels);
    RRP_DBC_W_GETTER(rrp::v22::CreatorObject, "|", creators);
    RRP_DBC_W_GETTER(rrp::v22::SongObject, ":", songs);

    rrp::v22::PageInfo pageInfo;
    std::string hash;
};

