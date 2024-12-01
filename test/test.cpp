#include <rrp/rrp.hpp>
#include <catch2/catch_test_macros.hpp>

#define DELIM(str) constexpr static std::string_view DELIM = str;
struct SimpleResponse
{
    int a = 5;
    int b = 6;
    int c = 7;
    constexpr static std::string_view DELIM = ",";
};

TEST_CASE("SimpleIntegers")
{
    auto sr = rrp::rrp<SimpleResponse>("1,2,3");
    REQUIRE(sr.a == 1);
    REQUIRE(sr.b == 2);
    REQUIRE(sr.c == 3);
}

struct StringDelim
{
    int a, b, c;
    constexpr static std::string_view DELIM = "---";
};

TEST_CASE("StringDelim")
{
    auto sr = rrp::rrp<StringDelim>("1---2---3");
    REQUIRE(sr.a == 1);
    REQUIRE(sr.b == 2);
    REQUIRE(sr.c == 3);
}

TEST_CASE("SimpleDefaultValues")
{
    auto sr = rrp::rrp<SimpleResponse>("a,b,c");
    INFO(sr.a);
    REQUIRE(sr.a == 5);
    REQUIRE(sr.b == 6);
    REQUIRE(sr.c == 7);
}


struct SimpleFloat
{
    float a, b, c;
    constexpr static std::string_view DELIM = ",";
};

TEST_CASE("SimpleFloat")
{
    auto r = rrp::rrp<SimpleFloat>("1.0,2,3");
    INFO(r.a << " " << r.b << " " << r.c);
    REQUIRE(r.a == 1.0f);
    REQUIRE(r.b == 2.0f);
    REQUIRE(r.c == 3.0f);

    r = rrp::rrp<SimpleFloat>("1.5356,2.79183,36.57132");
    REQUIRE(r.a == 1.5356f);
    REQUIRE(r.b == 2.79183f);
    REQUIRE(r.c == 36.57132f);
}

struct Strings
{
    int a;
    std::string b;
    std::string c;
    DELIM(",");
};

TEST_CASE("Strings")
{
    auto r = rrp::rrp<Strings>("1,hello world,test");
    REQUIRE(r.a == 1);
    REQUIRE(r.b == "hello world");
    REQUIRE(r.c == "test");
}

struct NestedA
{
    int a, b, c;
    DELIM(",")
    struct NestedB
    {
        float a, b, c;
        DELIM("-")
    } nested;
};

TEST_CASE("Nested")
{
    auto r = rrp::rrp<NestedA>("1,2,3,1.5-2.3-7.7");
    REQUIRE(r.a == 1);
    REQUIRE(r.b == 2);
    REQUIRE(r.c == 3);
    REQUIRE(r.nested.a == 1.5f);
    REQUIRE(r.nested.b == 2.3f);
    REQUIRE(r.nested.c == 7.7f);
}



/*GETGJLEVELS*/

struct LevelObject
{
    int id;
    std::string levelName;
    DELIM(",");
};

struct Creator
{
    int userID;
    std::string userName;
    int accountID;
    DELIM(":");
};

struct GetGJLevels21
{
    LevelObject level;
    Creator creator;
    DELIM("#");
};

TEST_CASE("GetGJLevels21")
{
    auto r = rrp::rrp<GetGJLevels21>("1,Stereo Madness#1:robtop:1");
    REQUIRE(r.level.id == 1);
    REQUIRE(r.level.levelName == "Stereo Madness");
    REQUIRE(r.creator.userID == 1);
    REQUIRE(r.creator.userName == "robtop");
    REQUIRE(r.creator.accountID == 1);
}