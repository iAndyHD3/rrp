#pragma once

#include <rrp/rrp.hpp>

namespace rrp::v22
{

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