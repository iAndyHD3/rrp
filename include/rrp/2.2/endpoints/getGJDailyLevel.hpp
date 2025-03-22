#pragma once
#include "rrp/rrp.hpp"

namespace rrp::v22
{

struct getGJDailyLevel : public SimpleDelimSeparatedBase
{
    RRP_DELIM("|");
    int levelIndex;
    int secondsLeft;
};


}