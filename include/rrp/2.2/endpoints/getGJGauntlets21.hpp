#pragma once
#include <rrp/rrp.hpp>
#include <rrp/2.2/Enums.hpp>
namespace rrp::v22
{

struct GauntletObject : public ValueMapContainer
{
    RRP_DELIM(":");
    RRP_IVM_W_GETTER(Gauntlet, 1, gauntletID)
    RRP_IVM_DBC_W_GETTER(int, 3, ",", levels);
};

struct getGJGauntlets21
{
    RRP_DELIM("#");
    RRP_DBC_W_GETTER(GauntletObject, "|", gauntlets)
    std::string_view hash;
};

}