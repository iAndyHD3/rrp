#pragma once
#include "../rrp.hpp"
#include <cstdint>
#include <string_view>
#include "../base64.h"
#include "rrp/base64.h"

namespace rrp::v22
{

struct CommentObject : rrp::ValueMapContainer
{
    RRP_DELIM("~");

    RRP_IVM_W_GETTER(int32_t, 1, commentID)
    RRP_B64_IVM_W_GETTER(std::string_view, 2, comment)
    RRP_IVM_W_GETTER(int32_t, 3, authorAccountID)
    RRP_IVM_W_GETTER(int32_t, 4, likes)
    RRP_IVM_W_GETTER(int32_t, 5, dislikes)
    RRP_IVM_W_GETTER(int32_t, 6, messageID)
    RRP_IVM_W_GETTER(bool, 7, spam)
    RRP_IVM_W_GETTER(std::string_view, 9, age)
    RRP_IVM_W_GETTER(uint8_t, 10, percent)
    RRP_IVM_W_GETTER(uint8_t, 11, modBadge)

    struct RGBColor : public SimpleDelimSeparatedBase
    {
        RRP_DELIM(",");
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    RRP_IVM_W_GETTER(RGBColor, 12, moderatorChatColor)
};

}
