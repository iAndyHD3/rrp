#pragma once
#include "CommentObject.hpp"
#include "rrp/rrp.hpp"

namespace rrp::v22
{

struct CommentUserInfo : ValueMapContainer
{
    RRP_DELIM("~");
    RRP_IVM_W_GETTER(std::string_view, 1, userName)
    RRP_IVM_W_GETTER(std::uint16_t, 9, iconID)
    RRP_IVM_W_GETTER(std::uint16_t, 10, color)
    RRP_IVM_W_GETTER(std::uint16_t, 11, color2)
    RRP_IVM_W_GETTER(std::uint32_t, 14, iconType)
    RRP_IVM_W_GETTER(std::uint32_t, 15, special)
    RRP_IVM_W_GETTER(std::uint32_t, 16, accountID)
};

struct CommentObjectWUserInfo : SimpleDelimSeparatedBase
{
    RRP_DELIM(":");
    CommentObject comment;
    CommentUserInfo user;
};

struct getGJComments21
{
    RRP_DELIM("");
    RRP_DBC_W_GETTER(CommentObjectWUserInfo, "|", comments);
};

}