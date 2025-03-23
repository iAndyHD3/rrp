#pragma once

#include <rrp/rrp.hpp>
#include <rrp/2.2/UserObject.hpp>

namespace rrp::v22
{

struct getGJScores20
{
    RRP_DELIM("");
    RRP_DBC_W_GETTER(UserObject, "|", users);
};

}