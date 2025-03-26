#pragma once
#include <cstdint>
#include <rrp/rrp.hpp>
#include <rrp/base64.h>
#include <string_view>
#include "Enums.hpp"
#include "rrp/2.2/MessageObject.hpp"

namespace rrp::v22
{
struct LevelObject : public rrp::ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = ":";

    // Grouping by type size to avoid padding

    // 4-byte types (std::uint32_t and std::int32_t)
    RRP_IVM_W_GETTER(std::uint32_t, 1, levelID)
    RRP_IVM_W_GETTER(std::uint32_t, 5, version)
    RRP_IVM_W_GETTER(std::uint32_t, 6, playerID)
    RRP_IVM_W_GETTER(std::uint32_t, 10, downloads)
    RRP_IVM_W_GETTER(std::uint32_t, 14, likes)
    RRP_IVM_W_GETTER(std::uint32_t, 16, dislikes)
    RRP_IVM_W_GETTER(std::uint32_t, 19, featureScore)
    RRP_IVM_W_GETTER(std::uint32_t, 30, copiedID)
    RRP_IVM_W_GETTER(std::uint32_t, 35, customSongID)
    RRP_IVM_W_GETTER(std::uint32_t, 41, dailyNumber)
    RRP_IVM_W_GETTER(std::uint32_t, 45, objects)
    RRP_IVM_W_GETTER(std::uint32_t, 46, editorTime)
    RRP_IVM_W_GETTER(std::uint32_t, 47, editorTimeCopies)
    RRP_IVM_W_GETTER(std::int32_t, 54, unknown)
    RRP_IVM_W_GETTER(std::uint32_t, 57, verificationTime)

    // 1-byte types (std::uint8_t)
    RRP_IVM_W_GETTER(std::uint8_t, 8, difficultyDenominator)
    RRP_IVM_W_GETTER(std::uint8_t, 9, difficultyNumerator)
    RRP_IVM_W_GETTER(std::uint8_t, 12, officialSong)
    RRP_IVM_W_GETTER(std::uint8_t, 13, gameVersion)
    RRP_IVM_W_GETTER(std::uint8_t, 15, length)
    RRP_IVM_W_GETTER(std::uint8_t, 18, stars)
    RRP_IVM_W_GETTER(std::uint8_t, 37, coins)
    RRP_IVM_W_GETTER(std::uint8_t, 39, starsRequested)
    RRP_IVM_W_GETTER(std::uint8_t, 42, epic)
    RRP_IVM_W_GETTER(std::uint8_t, 43, demonDifficulty)


    RRP_IVM_W_GETTER(bool, 17, demon)
    RRP_IVM_W_GETTER(bool, 25, auto_)
    RRP_IVM_W_GETTER(bool, 31, twoPlayer)
    RRP_IVM_W_GETTER(bool, 38, verifiedCoins)
    RRP_IVM_W_GETTER(bool, 40, lowDetailMode)
    RRP_IVM_W_GETTER(bool, 44, isGauntlet)

    RRP_IVM_W_GETTER(std::string_view, 2, levelName)

    RRP_B64_IVM_W_GETTER(std::string_view, 3, description)

    //Only in download endpoint
    RRP_IVM_W_GETTER(std::string_view, 4, levelString) 

    // Note: Unused
    RRP_IVM_W_GETTER(std::string_view, 26, recordString) 

    RRP_IVM_W_GETTER(std::string_view, 28, uploadDate)
    RRP_IVM_W_GETTER(std::string_view, 29, updateDate)
    RRP_IVM_W_GETTER(std::string_view, 36, extraString)

    // Note: Unused after early 2.1
    RRP_IVM_W_GETTER(std::string_view, 48, settingsString) 

    RRP_B64_XOR_IVM_W_GETTER(std::string_view, 27, password, "26364")

    RRP_IVM_DBC_W_GETTER(int32_t, 52, ",", songIDs)
    RRP_IVM_DBC_W_GETTER(int32_t, 53, ",", sfxIDs)

    //manual helpers
    DifficultyFace difficultyFace()
    {
        switch(demonDifficulty())
        {
            case 3: return DifficultyFace::EasyDemon;
            case 4: return DifficultyFace::MediumDemon;
            case 0: return DifficultyFace::HardDemon;
            case 5: return DifficultyFace::InsaneDemon;
            case 6: return DifficultyFace::ExtremeDemon;
        }

        auto dem = difficultyDenominator();
        if(dem == 0) return DifficultyFace::NA;
        switch(difficultyNumerator() / dem)
        {
            case 1: return DifficultyFace::Easy;
            case 2: return DifficultyFace::Normal;
            case 3: return DifficultyFace::Hard;
            case 4: return DifficultyFace::Harder;
            case 5: return DifficultyFace::Insane;
        }

        return DifficultyFace::NA;
    }

    LevelRating rating()
    {
        if(featureScore() > 0 && epic() == 0) return LevelRating::Featured;

        switch(epic())
        {
            case 0: return LevelRating::None;
            case 1: return LevelRating::Epic;
            case 2: return LevelRating::Legendary;
            case 3: return LevelRating::Mythic;
        }
        return LevelRating::None;
    }
};

}