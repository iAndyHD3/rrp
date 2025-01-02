#pragma once
#include "common.hpp"
#include <cstdint>
#include <rrp/rrp.hpp>

namespace rrp::v22
{

struct GauntletObject : public ValueMapContainer
{
    RRP_DELIM(":");
    RRP_IVM_W_GETTER(std::uint32_t, 1, gauntletID)
    RRP_IVM_DBC_W_GETTER(int, 3, ",", levels);
};

struct GetGauntlets
{
    RRP_DELIM("#");
    RRP_DBC_W_GETTER(GauntletObject, "|", gauntlets)
    std::string_view hash;
};

}