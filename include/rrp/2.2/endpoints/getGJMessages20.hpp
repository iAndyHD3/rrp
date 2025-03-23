#pragma once

#include "rrp/2.2/PageInfo.hpp"
#include "rrp/rrp.hpp"
#include <rrp/2.2/MessageObject.hpp>

namespace rrp::v22
{

struct getGJMessages20 : SimpleDelimSeparatedBase
{
    RRP_DELIM("#");
    RRP_DBC_W_GETTER(MessageObjectNoContent, "|", messages)
    PageInfo pageInfo;
};

}