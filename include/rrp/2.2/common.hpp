#include <rrp/rrp.hpp>

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

template<reflect::fixed_string D = "">
struct LevelObject : public rrp::ValueMapContainer
{
    static constexpr reflect::fixed_string DELIM = D;

    // Integer getters
    RRP_IVM_W_GETTER(int, 1, levelID);
    RRP_IVM_W_GETTER(int, 5, version);
    RRP_IVM_W_GETTER(int, 6, playerID);
    RRP_IVM_W_GETTER(int, 8, difficultyDenominator);
    RRP_IVM_W_GETTER(int, 9, difficultyNumerator);
    RRP_IVM_W_GETTER(int, 10, downloads);
    //RRP_IVM_W_GETTER(int, 11, setCompletes); // Note: Removed in update 2.1
    RRP_IVM_W_GETTER(int, 12, officialSong);
    RRP_IVM_W_GETTER(int, 13, gameVersion);
    RRP_IVM_W_GETTER(int, 14, likes);
    RRP_IVM_W_GETTER(int, 15, length);
    RRP_IVM_W_GETTER(int, 16, dislikes);
    RRP_IVM_W_GETTER(int, 18, stars);
    RRP_IVM_W_GETTER(int, 19, featureScore);
    RRP_IVM_W_GETTER(int, 30, copiedID);
    RRP_IVM_W_GETTER(int, 35, customSongID);
    RRP_IVM_W_GETTER(int, 37, coins);
    RRP_IVM_W_GETTER(int, 39, starsRequested);
    RRP_IVM_W_GETTER(int, 41, dailyNumber); // Note: Specific to daily/weekly levels
    RRP_IVM_W_GETTER(int, 42, epic);
    RRP_IVM_W_GETTER(int, 43, demonDifficulty);
    RRP_IVM_W_GETTER(int, 45, objects);
    RRP_IVM_W_GETTER(int, 46, editorTime);
    RRP_IVM_W_GETTER(int, 47, editorTimeCopies);
    RRP_IVM_W_GETTER(int, 54, unknown);
    RRP_IVM_W_GETTER(int, 57, verificationTime);

    // Bool getters
    RRP_IVM_W_GETTER(bool, 17, demon);
    RRP_IVM_W_GETTER(bool, 25, auto_);
    RRP_IVM_W_GETTER(bool, 31, twoPlayer);
    RRP_IVM_W_GETTER(bool, 38, verifiedCoins);
    RRP_IVM_W_GETTER(bool, 40, lowDetailMode);
    RRP_IVM_W_GETTER(bool, 44, isGauntlet);

    // String getters
    RRP_IVM_W_GETTER(std::string, 2, levelName);
    RRP_IVM_W_GETTER(std::string, 3, description);
    RRP_IVM_W_GETTER(std::string, 4, levelString);
    RRP_IVM_W_GETTER(std::string, 26, recordString); // Note: Unused
    RRP_IVM_W_GETTER(std::string, 28, uploadDate);
    RRP_IVM_W_GETTER(std::string, 29, updateDate);
    RRP_IVM_W_GETTER(std::string, 36, extraString);
    RRP_IVM_W_GETTER(std::string, 48, settingsString); // Note: Unused after early 2.1

    // Encrypted String getters
    RRP_IVM_W_GETTER(std::string, 27, password);

    // Comma-Separated List getters
    RRP_IVM_W_GETTER(std::string, 52, songIDs);
    RRP_IVM_W_GETTER(std::string, 53, sfxIDs);

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


template<reflect::fixed_string D = "">
struct CreatorObject : rrp::SimpleDelimSeparatedBase
{
    static constexpr reflect::fixed_string DELIM = D;
    int userID;
    std::string userName;
    int accountID;
};

}