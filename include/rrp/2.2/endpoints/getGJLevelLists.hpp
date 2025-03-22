#pragma once
#include <rrp/rrp.hpp>
#include <rrp/2.2/ListObject.hpp>
#include <rrp/2.2/CreatorObject.hpp>
#include <rrp/2.2/PageInfo.hpp>


namespace rrp::v22
{
struct getGJLevelLists
{
    RRP_DELIM("#");
    RRP_DBC_W_GETTER(rrp::v22::ListObject, "|", lists);
    RRP_DBC_W_GETTER(rrp::v22::CreatorObject, "|", creators);

    rrp::v22::PageInfo pageInfo;
    std::string_view hash;
};

}