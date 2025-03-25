#pragma once

#include <cstdint>
#include <rrp/rrp.hpp>
#include <string_view>
#include <rrp/xor_base64.hpp>


namespace rrp::v22
{

struct MessageObject : ValueMapContainer
{
    RRP_DELIM(":");

    RRP_IVM_W_GETTER(std::uint32_t, 1, messageID)
    RRP_IVM_W_GETTER(std::uint32_t, 2, accountID)
    RRP_IVM_W_GETTER(std::uint32_t, 3, playerID)

    RRP_B64_IVM_W_GETTER(std::string_view, 4, title)


    //smh
    RRP_B64_XOR_IVM_W_GETTER(std::string_view, 5, messageContent, "14251")


    RRP_IVM_W_GETTER(std::string_view, 6, userName)
    RRP_IVM_W_GETTER(std::string_view, 7, age)
    RRP_IVM_W_GETTER(bool, 8, read)
    RRP_IVM_W_GETTER(bool, 8, sender)

};

//getMessages20.php doesn't return key 5
struct MessageObjectNoContent : ValueMapContainer
{
    RRP_DELIM(":");

    RRP_IVM_W_GETTER(std::uint32_t, 1, messageID)
    RRP_IVM_W_GETTER(std::uint32_t, 2, accountID)
    RRP_IVM_W_GETTER(std::uint32_t, 3, playerID)

    RRP_B64_IVM_W_GETTER(std::string_view, 4, title)

    RRP_IVM_W_GETTER(std::string_view, 6, userName)
    RRP_IVM_W_GETTER(std::string_view, 7, age)
    RRP_IVM_W_GETTER(bool, 8, read)
    RRP_IVM_W_GETTER(bool, 8, sender)

};


}