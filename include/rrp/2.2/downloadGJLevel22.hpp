#pragma once
#include "rrp/rrp.hpp"
#include "LevelObject.hpp"

namespace rrp::v22
{

struct DownloadGJLevel22 : SimpleDelimSeparatedBase
{
    RRP_DELIM("#");
    LevelObject level;
    std::string_view hash1;
    std::string_view hash2;
};

}