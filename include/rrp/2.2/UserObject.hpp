#pragma once
#include "rrp/rrp.hpp"
#include <cstdint>


namespace rrp::v22
{

struct UserBeatenDemons : public rrp::SimpleDelimSeparatedBase
{
    RRP_DELIM(",");
    std::uint32_t easy;
    std::uint32_t medium;
    std::uint32_t hard;
    std::uint32_t insane;
    std::uint32_t extreme;
    std::uint32_t easyPlatformer;
    std::uint32_t mediumPlatformer;
    std::uint32_t hardPlatformer;
    std::uint32_t insanePlatformer;
    std::uint32_t extremePlatformer;
    std::uint32_t weekly;
    std::uint32_t gauntlet;

};

struct UserObject : ValueMapContainer
{
    RRP_DELIM(":");

    RRP_IVM_W_GETTER(std::uint8_t, 49, modlevel);
    RRP_IVM_W_GETTER(std::uint8_t, 50, commentHistoryState);
    RRP_IVM_W_GETTER(std::uint8_t, 18, messageState);
    RRP_IVM_W_GETTER(std::uint8_t, 19, friendsState);
    RRP_IVM_W_GETTER(std::uint8_t, 31, friendstate);

    RRP_IVM_W_GETTER(bool, 29, isRegistered);
    RRP_IVM_W_GETTER(bool, 41, NewFriendRequest);

    RRP_IVM_W_GETTER(std::uint16_t, 9, iconID);
    RRP_IVM_W_GETTER(std::uint16_t, 10, color);
    RRP_IVM_W_GETTER(std::uint16_t, 11, color2);
    RRP_IVM_W_GETTER(std::uint16_t, 21, accIcon);
    RRP_IVM_W_GETTER(std::uint16_t, 22, accShip);
    RRP_IVM_W_GETTER(std::uint16_t, 23, accBall);
    RRP_IVM_W_GETTER(std::uint16_t, 24, accBird);
    RRP_IVM_W_GETTER(std::uint16_t, 25, accDart);
    RRP_IVM_W_GETTER(std::uint16_t, 26, accRobot);
    RRP_IVM_W_GETTER(std::uint16_t, 27, accStreak);
    RRP_IVM_W_GETTER(std::uint16_t, 28, accGlow);
    RRP_IVM_W_GETTER(std::uint16_t, 48, accExplosion);
    RRP_IVM_W_GETTER(std::uint16_t, 43, accSpider);
    RRP_IVM_W_GETTER(std::uint16_t, 51, color3);
    RRP_IVM_W_GETTER(std::uint16_t, 53, accSwing);
    RRP_IVM_W_GETTER(std::uint16_t, 54, accJetpack);

    RRP_IVM_W_GETTER(std::uint32_t, 2, userID);
    RRP_IVM_W_GETTER(std::uint32_t, 3, stars);
    RRP_IVM_W_GETTER(std::uint32_t, 4, demons);
    RRP_IVM_W_GETTER(std::uint32_t, 6, ranking);
    RRP_IVM_W_GETTER(std::uint32_t, 7, accountHighlight);
    RRP_IVM_W_GETTER(std::uint32_t, 8, creatorpoints);
    RRP_IVM_W_GETTER(std::uint32_t, 13, secretCoins);
    RRP_IVM_W_GETTER(std::uint32_t, 14, iconType);
    RRP_IVM_W_GETTER(std::uint32_t, 15, special);
    RRP_IVM_W_GETTER(std::uint32_t, 16, accountID);
    RRP_IVM_W_GETTER(std::uint32_t, 17, usercoins);
    RRP_IVM_W_GETTER(std::uint32_t, 30, globalRank);
    RRP_IVM_W_GETTER(std::uint32_t, 38, messages);
    RRP_IVM_W_GETTER(std::uint32_t, 39, friendRequests);
    RRP_IVM_W_GETTER(std::uint32_t, 40, newFriends);
    RRP_IVM_W_GETTER(std::uint32_t, 46, diamonds);
    RRP_IVM_W_GETTER(std::uint32_t, 52, moons);



    RRP_IVM_W_GETTER(std::string_view, 1, userName);
    RRP_IVM_W_GETTER(std::string_view, 20, youTube);
    RRP_IVM_W_GETTER(std::string_view, 42, age);
    RRP_IVM_W_GETTER(std::string_view, 44, twitter);
    RRP_IVM_W_GETTER(std::string_view, 45, twitch);

    
    //RRP_IVM_W_GETTER(std::string_view, 55, demonsString);

    RRP_IVM_W_GETTER(UserBeatenDemons, 55, beatenDemons)

    RRP_IVM_W_GETTER(std::string_view, 56, classicLevels);
    RRP_IVM_W_GETTER(std::string_view, 57, platformerLevels);


};

}