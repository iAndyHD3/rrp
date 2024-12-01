#include <rrp/rrp.hpp>
#include <catch2/catch_test_macros.hpp>

struct SimpleResponse
{
    int a;
    int b;
    int c;
    constexpr static inline std::string_view DELIM = ",";
};

TEST_CASE("Simple")
{
    auto sr = rrp::rrp<SimpleResponse>("1,2,3");
    REQUIRE(sr.a == 1);
    REQUIRE(sr.b == 2);
    REQUIRE(sr.c == 3);
}
