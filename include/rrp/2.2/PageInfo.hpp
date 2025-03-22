#pragma once
#include <rrp/rrp.hpp>


namespace rrp::v22
{

struct PageInfo : public rrp::SimpleDelimSeparatedBase
{
    RRP_DELIM(":");
    int total;
    int offset;
    int amount;
};
    

}