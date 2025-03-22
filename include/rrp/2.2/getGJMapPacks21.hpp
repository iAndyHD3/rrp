#pragma once
#include "MappackObject.hpp"
#include "PageInfo.hpp"

namespace rrp::v22
{

struct GetGJMapPacks21
{
    RRP_DELIM("#");

    RRP_DBC_W_GETTER(MappackObject, "|", mappacks)
    PageInfo pageInfo;
    std::string_view hash;

};

}