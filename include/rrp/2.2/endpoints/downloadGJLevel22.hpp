#pragma once
#include "rrp/2.2/LevelObject.hpp"
#include "rrp/rrp.hpp"

namespace rrp::v22
{

struct downloadGJLevel22 : SimpleDelimSeparatedBase
{
    RRP_DELIM("#");
    LevelObject level;
    std::string_view hash1;
    std::string_view hash2;
};

}