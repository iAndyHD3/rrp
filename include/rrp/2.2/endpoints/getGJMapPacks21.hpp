#pragma once
#include <rrp/2.2/MappackObject.hpp>
#include <rrp/2.2/PageInfo.hpp>

namespace rrp::v22
{

struct getGJMapPacks21
{
    RRP_DELIM("#");

    RRP_DBC_W_GETTER(MappackObject, "|", mappacks)
    PageInfo pageInfo;
    std::string_view hash;

};

}