#pragma once
#include "common.hpp"
#include "rrp/rrp.hpp"

struct GetLevelLists
{
    RRP_DELIM("#");
    RRP_DBC_W_GETTER(rrp::v22::ListObject, "|", lists);
    RRP_DBC_W_GETTER(rrp::v22::CreatorObject, "|", creators);

    rrp::v22::PageInfo pageInfo;
    std::string_view hash;
};