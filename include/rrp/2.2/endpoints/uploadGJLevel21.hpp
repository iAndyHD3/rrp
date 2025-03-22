#pragma once

#include <optional>
#include <rrp/rrp.hpp>

namespace rrp::v22
{

struct uploadGJLevel21 : SimpleIntResponseBase
{
    std::optional<std::int32_t> value;


    std::optional<std::int32_t>& levelID() { return value; }
    std::optional<std::int32_t>& listID() { return value; }
};

}