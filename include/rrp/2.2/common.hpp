#pragma once
#include <rrp/rrp.hpp>
#include <cstdint>

namespace rrp::v22
{

enum class DifficultyFace
{
    NA,
    Easy,
    Normal,
    Hard,
    Harder,
    Insane,
    EasyDemon,
    MediumDemon,
    HardDemon,
    InsaneDemon,
    ExtremeDemon
};

enum class LevelRating
{
    None,
    Star,
    Featured,
    Epic,
    Legendary,
    Mythic,
};


struct LevelObject : public rrp::ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = ":";

    // Grouping by type size to avoid padding

    // 4-byte types (std::uint32_t and std::int32_t)
    RRP_IVM_W_GETTER(std::uint32_t, 1, levelID);
    RRP_IVM_W_GETTER(std::uint32_t, 5, version);
    RRP_IVM_W_GETTER(std::uint32_t, 6, playerID);
    RRP_IVM_W_GETTER(std::uint32_t, 10, downloads);
    RRP_IVM_W_GETTER(std::uint32_t, 14, likes);
    RRP_IVM_W_GETTER(std::uint32_t, 16, dislikes);
    RRP_IVM_W_GETTER(std::uint32_t, 19, featureScore);
    RRP_IVM_W_GETTER(std::uint32_t, 30, copiedID);
    RRP_IVM_W_GETTER(std::uint32_t, 35, customSongID);
    RRP_IVM_W_GETTER(std::uint32_t, 41, dailyNumber);
    RRP_IVM_W_GETTER(std::uint32_t, 45, objects);
    RRP_IVM_W_GETTER(std::uint32_t, 46, editorTime);
    RRP_IVM_W_GETTER(std::uint32_t, 47, editorTimeCopies);
    RRP_IVM_W_GETTER(std::int32_t, 54, unknown);
    RRP_IVM_W_GETTER(std::uint32_t, 57, verificationTime);

    // 1-byte types (std::uint8_t)
    RRP_IVM_W_GETTER(std::uint8_t, 8, difficultyDenominator);
    RRP_IVM_W_GETTER(std::uint8_t, 9, difficultyNumerator);
    RRP_IVM_W_GETTER(std::uint8_t, 12, officialSong);
    RRP_IVM_W_GETTER(std::uint8_t, 13, gameVersion);
    RRP_IVM_W_GETTER(std::uint8_t, 15, length);
    RRP_IVM_W_GETTER(std::uint8_t, 18, stars);
    RRP_IVM_W_GETTER(std::uint8_t, 37, coins);
    RRP_IVM_W_GETTER(std::uint8_t, 39, starsRequested);
    RRP_IVM_W_GETTER(std::uint8_t, 42, epic);
    RRP_IVM_W_GETTER(std::uint8_t, 43, demonDifficulty);


    // Bool getters
    RRP_IVM_W_GETTER(bool, 17, demon);
    RRP_IVM_W_GETTER(bool, 25, auto_);
    RRP_IVM_W_GETTER(bool, 31, twoPlayer);
    RRP_IVM_W_GETTER(bool, 38, verifiedCoins);
    RRP_IVM_W_GETTER(bool, 40, lowDetailMode);
    RRP_IVM_W_GETTER(bool, 44, isGauntlet);

    // String getters
    RRP_IVM_W_GETTER(std::string_view, 2, levelName);

    RRP_IVM_W_GETTER(std::string_view, 3, description);
    RRP_IVM_W_GETTER(std::string_view, 4, levelString);
    RRP_IVM_W_GETTER(std::string_view, 26, recordString); // Note: Unused
    RRP_IVM_W_GETTER(std::string_view, 28, uploadDate);
    RRP_IVM_W_GETTER(std::string_view, 29, updateDate);
    RRP_IVM_W_GETTER(std::string_view, 36, extraString);
    RRP_IVM_W_GETTER(std::string_view, 48, settingsString); // Note: Unused after early 2.1

    // Encrypted String getters
    RRP_IVM_W_GETTER(std::string_view, 27, password);

    // Comma-Separated List getters
    RRP_IVM_W_GETTER(std::string_view, 52, songIDs);
    RRP_IVM_W_GETTER(std::string_view, 53, sfxIDs);

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



struct CreatorObject : rrp::SimpleDelimSeparatedBase
{
    static constexpr reflect::fixed_string DELIM = ":";
    int userID;
    std::string userName;
    int accountID;
};

struct SongObject : rrp::ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = "~|~";
    RRP_IVM_W_GETTER(int, 1, songID);
    RRP_IVM_W_GETTER(int, 2, artistID);
    RRP_IVM_W_GETTER(int, 5, sizeInMB);
    RRP_IVM_W_GETTER(int, 9, songPriority);
    RRP_IVM_W_GETTER(int, 9, nongEnum);
    RRP_IVM_W_GETTER(int, 14, newType);

    RRP_IVM_W_GETTER(std::string_view, 2, name);
    RRP_IVM_W_GETTER(std::string_view, 4, artistName);
    RRP_IVM_W_GETTER(std::string_view, 6, videoID);
    RRP_IVM_W_GETTER(std::string_view, 7, artistYTURL);
    RRP_IVM_W_GETTER(std::string_view, 10, downloadLink);
    //TODO parse this (simple delim container)
    RRP_IVM_W_GETTER(std::string_view, 12, extraArtistsID);
    RRP_IVM_W_GETTER(std::string_view, 15, extraArstistNames);

    RRP_IVM_W_GETTER(bool, 8, isArtistScouted);
    RRP_IVM_W_GETTER(bool, 13, isNew);

};

struct PageInfo : public rrp::SimpleDelimSeparatedBase
{
    RRP_DELIM(":");
    int total;
    int offset;
    int amount;
};

#define RRP_IVM_DBC_W_GETTER(type, index, delim, name) \
    rrp::IndexedValueMap<rrp::DelimBasedContainer<type, delim>, index> m_##name; \
    std::vector<type> name() { return m_##name.value.values; }

struct ListObject : public rrp::ValueMapContainer
{
    RRP_DELIM(":");

    // Integer getters
    RRP_IVM_W_GETTER(std::uint32_t, 1, listID);                    // The id of the list
    RRP_IVM_W_GETTER(std::uint32_t, 5, version);                  // The version of the list published
    RRP_IVM_W_GETTER(std::int32_t, 7, difficulty);               // The difficulty face for the list. -1 = N/A, 0 = Auto, 1 = Easy, 2 = Normal, 3 = Hard, 4 = Harder, 5 = Insane, 6 = Easy Demon, 7 = Medium Demon, 8 = Hard Demon, 9 = Insane Demon, 10 = Extreme Demon
    RRP_IVM_W_GETTER(std::uint32_t, 10, downloads);               // The amount of times the list has been downloaded
    RRP_IVM_W_GETTER(std::int32_t, 14, likes);                   // likes - dislikes
    RRP_IVM_W_GETTER(std::uint32_t, 49, accountID);               // The account ID of the list author
    RRP_IVM_W_GETTER(std::int32_t, 55, listReward);              // The amount of diamonds awarded upon beating the required amount of levels in the list
    RRP_IVM_W_GETTER(std::uint32_t, 56, listRewardRequirement);   // The amount of levels needed to claim the list reward

    // Bool getters
    RRP_IVM_W_GETTER(bool, 19, rated);                  // If the list is rated or not

    // String getters
    RRP_IVM_W_GETTER(std::string_view, 2, listName);          // The name of the list
    RRP_IVM_W_GETTER(std::string_view, 3, description);      // The list description, encoded in base64
    RRP_IVM_W_GETTER(std::string_view, 28, uploadDate);       // The Unix timestamp of when the list was uploaded
    RRP_IVM_W_GETTER(std::string_view, 29, updateDate);       // The Unix timestamp of when the list was last updated
    RRP_IVM_W_GETTER(std::string_view, 50, username);         // The username of the list author

    // Comma-Separated List getters


    RRP_IVM_DBC_W_GETTER(std::uint32_t, 51, ",", levelIDs);

};




}