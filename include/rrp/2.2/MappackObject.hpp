#pragma once
#include "../rrp.hpp"
#include <cstdint>
#include <string_view>

namespace rrp::v22
{

struct MappackObject : rrp::ValueMapContainer
{
    RRP_DELIM(":");

    RRP_IVM_W_GETTER(uint32_t, 1, packID)
    RRP_IVM_W_GETTER(std::string_view, 2, name)
    RRP_IVM_DBC_W_GETTER(uint32_t, 3, ",", levels)
    RRP_IVM_W_GETTER(uint8_t, 4, stars)
    RRP_IVM_W_GETTER(uint8_t, 5, coins)
    RRP_IVM_W_GETTER(uint8_t, 6, difficulty)

    struct RGBColor : public SimpleDelimSeparatedBase
    {
        RRP_DELIM(",");
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    
    RRP_IVM_W_GETTER(RGBColor, 7, textColor)
    //RRP_IVM_DBC_W_GETTER(RGBColor, 8, ",", barColor)

};

}