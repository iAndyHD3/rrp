#pragma once
#include <rrp/rrp.hpp>
#include <rrp/2.2/CommentObject.hpp>

namespace rrp::v22
{

struct getGJAccountComments20 : rrp::DelimBasedContainerBase
{
    RRP_DELIM("");
    RRP_DBC_W_GETTER(CommentObject, "|", comments);
};


}