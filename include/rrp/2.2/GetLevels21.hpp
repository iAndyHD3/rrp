#include "common.hpp"

struct GJLevels21
{
    static constexpr reflect::fixed_string DELIM = "#";
    RRP_DBC_W_GETTER(rrp::v22::LevelObject<":">, "|", levels);
    RRP_DBC_W_GETTER(rrp::v22::CreatorObject<":">, "|", creators);
};