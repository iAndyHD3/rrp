#pragma once
#include <rrp/rrp.hpp>
#include <rrp/2.2/CommentObject.hpp>

namespace rrp::v22
{

struct getGJAccountComments20 : rrp::DelimBasedContainer<CommentObject, "|">
{
    std::vector<CommentObject>& comments() { return values; }
};

}