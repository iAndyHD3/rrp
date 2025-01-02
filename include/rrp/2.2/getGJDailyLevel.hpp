#pragma once
#include "rrp/rrp.hpp"

namespace rrp::v22
{

struct GetDailyLevel : public SimpleDelimSeparatedBase
{
    RRP_DELIM("|");
    int levelIndex;
    int secondsLeft;
};


}