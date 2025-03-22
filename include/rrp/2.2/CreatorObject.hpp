#pragma once
#include <rrp/rrp.hpp>

namespace rrp::v22
{
struct CreatorObject : rrp::SimpleDelimSeparatedBase
{
    static constexpr reflect::fixed_string DELIM = ":";
    int userID;
    std::string userName;
    int accountID;
};

}