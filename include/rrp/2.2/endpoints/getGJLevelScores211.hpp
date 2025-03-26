#pragma once
#include <rrp/2.2/LeaderboardScoreObject.hpp>


namespace rrp::v22
{

struct getGJLevelScores211
{
    RRP_DBC_W_GETTER(LeaderboardScoreObject, "|", scores)
};

}