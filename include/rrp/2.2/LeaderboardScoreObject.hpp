#pragma once
#include <rrp/rrp.hpp>
#include <string_view>


namespace rrp::v22
{

template<reflect::fixed_string D = "">
struct VMK
{
    static constexpr auto DELIM = D;
};



struct LeaderboardScoreObject : ValueMapContainer
{
    RRP_DELIM(":");

    RRP_IVM_W_GETTER(std::string_view, 1, userName)
    RRP_IVM_W_GETTER(int, 2, playerID)
    RRP_IVM_W_GETTER(int, 3, stars)
    RRP_IVM_W_GETTER(int, 4, demons)
    RRP_IVM_W_GETTER(int, 5, ranking)
    RRP_IVM_W_GETTER(int, 8, creatorPoints)
    RRP_IVM_W_GETTER(int, 9, icon)
    RRP_IVM_W_GETTER(int, 10, playerColor)
    RRP_IVM_W_GETTER(int, 11, playerColor2)
    RRP_IVM_W_GETTER(int, 13, coins)
    RRP_IVM_W_GETTER(int, 14, iconType)
    RRP_IVM_W_GETTER(int, 15, special)
    RRP_IVM_W_GETTER(int, 16, accountID)
    RRP_IVM_W_GETTER(int, 17, userCoins)
    RRP_IVM_W_GETTER(int, 46, diamonds)
    RRP_IVM_W_GETTER(int, 52, moons)
};

}
