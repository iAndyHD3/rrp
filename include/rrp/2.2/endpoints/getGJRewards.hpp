#pragma once
#include <cstdint>
#include <rrp/rrp.hpp>
#include <rrp/xor.hpp>
#include <rrp/base64.h>


namespace rrp::v22
{

struct ChestRewardEncodedData : SimpleDelimSeparatedBase
{
    RRP_DELIM(":");
    std::string randomString;
    uint32_t userID;
    int32_t chkNumber;
    std::string udid;
    uint32_t accountID;
    uint32_t smallChestRemainingTime;
    struct ChestRewardData : SimpleDelimSeparatedBase
    {
        RRP_DELIM(",");
        uint32_t orbs;
        uint32_t diamonds;
        uint8_t item1;
        uint8_t item2;
    } smallChestReward;

    uint32_t smallChestsClaimed;
    uint32_t largeChestRemainingTime;
    ChestRewardData largeChestReward;
    uint32_t largeChestsClaimed;
    int32_t rewardType;

    template<typename T>
    static T parse(std::string_view str)
    {
        std::string ret = xor_cycle(base64::decode(str.substr(5)), "59182");
        return SimpleDelimSeparatedBase::parse<ChestRewardEncodedData>(ret);
    }
};

struct getGJRewards
{
    RRP_DELIM("|");
    ChestRewardEncodedData data;
    std::string_view hash;


};

}