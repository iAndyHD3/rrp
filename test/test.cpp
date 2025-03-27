#include "rrp/2.2/CommentObject.hpp"
#include "rrp/2.2/endpoints/downloadGJMessage20.hpp"
#include "rrp/2.2/endpoints/getGJAccountComments20.hpp"
#include "rrp/2.2/endpoints/getGJLevelScores211.hpp"
#include "rrp/2.2/endpoints/getGJLevels21.hpp"
#include "rrp/2.2/endpoints/getGJSongInfo.hpp"
#include "rrp/rrp.hpp"
#include <matjson.hpp>
#include <rrp/2.2/endpoints/all.hpp>
#include <sstream>



template<typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os;
}


#include "ut.hpp"

#include <filesystem>
#include <rrp/rrp_serialize.hpp>

using namespace rrp;
using namespace rrp::v22;
using namespace boost::ut;




void printid(auto& ptr)
{
    std::cout << ptr.levelID() << "\n";

}

int fileCount = 0;
void log_glaze(const auto& response)
{

    std::cout << "Logging Type: " << reflect::type_name<std::remove_reference_t<decltype(response)>>() << '\n';

    std::string buffer = write_json(response).dump();
    std::cout << buffer << "\n";
    std::filesystem::path x = std::filesystem::temp_directory_path();
    std::filesystem::path file = x / std::string("rrp-test-" + std::to_string(fileCount) + ".json");
    std::ofstream f(file);
    f << buffer;
    std::cout << "SAVED TO: " << file.string() << std::endl;
    fileCount = fileCount + 1;
}

matjson::Value parseJsonFile(std::string_view fileName)
{
    std::string basePath = RRP_TEST_SOURCE_PATH;
    basePath.push_back('/');
    basePath += fileName;

    std::ifstream file(basePath);
    if(!file) return {};
    std::ostringstream content;
    content << file.rdbuf();

    auto json = matjson::parse(content.str());
    if(json) return *json;

    std::cout << std::string(json.unwrapErr());
    return {};
}

template<typename T>
std::string getResponseFromJson()
{
    static auto json = parseJsonFile("responses.json");

    if(!json.isObject()) return {};

    std::string_view typeName = reflect::type_name<T>();

    std::cout << typeName << "\n";

    if(auto v = json.get(typeName))
        if(auto s = (*v).asString())
            return *s;
    return {};
}

int main()
{

    static_assert(!Parsable<rrp::v22::getGJLevels21>);
    static_assert(!Parsable<std::string>);
    static_assert(!Parsable<int>);
    static_assert(!Parsable<float>);
    static_assert(Parsable<v22::CreatorObject>);

    "essential_funcs"_test = [](){
        auto tokens = splitByDelimToMap("0:a:1:bb:2:ccc:3:dddd", ":");
        expect(tokens[0] == "a");
        expect(tokens[1] == "bb");
        expect(tokens[2] == "ccc");
        expect(tokens[3] == "dddd");
    };

    "getGJLevels21.php"_test = [](){
        auto str = getResponseFromJson<getGJLevels21>();
        auto r = *rrp::rrp<rrp::v22::getGJLevels21>(str);

        //log_glaze(r);
        "bloodbath"_test = [&](){
            expect(r.levels()[0].levelID() == 10565740_i);
            expect(r.levels()[0].levelName() == "Bloodbath");
            expect(r.levels()[0].coins() == 0);
            expect(r.levels()[0].epic() == 0);
            expect(r.levels()[0].customSongID() == 467339_i);
            expect(r.levels()[0].copiedID() == 7679228_i);
            expect(r.levels()[0].length() == 3_i);
            expect(r.levels()[0].stars() == 10_i);
            expect(r.levels()[0].difficultyFace() == v22::DifficultyFace::ExtremeDemon);
            expect(r.levels()[0].rating() == v22::LevelRating::Featured);

            expect(r.creators()[0].userName == "Riot");
            expect(r.creators()[0].accountID == 37415_i);
            expect(r.creators()[0].userID == 503085_i);
        };

        "Bloodbath Auto"_test = [&](){
            expect(r.levels()[1].levelName() == "Bloodbath Z");
            expect(r.levels()[1].levelID() == 21761387_i);
            expect(r.levels()[1].customSongID() == 223469_i);
            expect(r.levels()[1].difficultyFace() == v22::DifficultyFace::MediumDemon);
            expect(r.levels()[1].rating() == v22::LevelRating::Featured);
        };

        "Songs"_test = [&](){
            expect(r.songs()[0].songID() == 223469_i);
            expect(r.songs()[1].songID() == 467339_i);
            expect(r.songs()[2].songID() == 513064_i);
            expect(r.songs()[3].songID() == 706340_i);

            expect(r.songs()[0].name() == "ParagonX9 - HyperioxX");
            expect(r.songs()[1].name() == "At the Speed of Light");
            expect(r.songs()[2].name() == "EnV - Uprise");
            expect(r.songs()[3].name() == "-At the Speed of Light- (8 bit Remix)");
        };

        "PageInfo"_test = [&](){
            expect(r.pageInfo.total == 4_i);
            expect(r.pageInfo.offset == 0_i);
            expect(r.pageInfo.amount == 10_i);
        };

        "Hash"_test = [&](){
            expect(r.hash == "1664b8bb919b0822a4408752c37a9fb5f651f813");
        };
    };


    "getGJLevelLists.php"_test = [](){
        auto str = getResponseFromJson<getGJLevelLists>();
        auto r = *rrp::rrp<rrp::v22::getGJLevelLists>(str);
        //log_glaze(r);
        
        expect(r.lists()[0].listID() == 10834_i);
        expect(r.lists()[0].listName() == "my mcdonalds order");
        expect(r.lists()[0].version() == 1_i);
        expect(r.lists()[0].m_levelIDs.value.values[0] == 78111123_i);
        expect(r.lists()[0].m_levelIDs.value.values[1] == 80840474_i);
        expect(r.lists()[0].m_levelIDs.value.values[2] == 20556675_i);
        expect(r.lists()[0].m_levelIDs.value.values[15] == 86742812_i);

        expect(r.creators()[0].userID == 10532982_i);
        expect(r.creators()[0].userName == "CreatorFreeze");
        expect(r.creators()[0].accountID == 1839061_i);

        expect(r.lists()[1].listID() == 4406_i);
        expect(r.lists()[1].listName() == "my mcdonalds order");
        expect(r.lists()[1].version() == 7_i);
        expect(r.lists()[1].m_levelIDs.value.values[0] == 25147297_i);
        expect(r.lists()[1].m_levelIDs.value.values[1] == 82785965_i);
        expect(r.lists()[1].m_levelIDs.value.values[2] == 11171792_i);


        expect(r.creators()[1].userID == 14827098_i);
        expect(r.creators()[1].userName == "tim55");
        expect(r.creators()[1].accountID == 4236858_i);

        expect(r.pageInfo.total == 9999_i);
        expect(r.pageInfo.offset == 0_i);
        expect(r.pageInfo.amount == 10_i);
    };
    "getGJGauntlets21.php"_test = [](){

        auto str = getResponseFromJson<getGJGauntlets21>();
        auto r = *rrp::rrp<rrp::v22::getGJGauntlets21>(str);
        //log_glaze(r);

        expect(r.gauntlets()[0].gauntletID() == Gauntlet::Fire);
        expect(r.gauntlets()[1].gauntletID() == Gauntlet::Ice);
        expect(r.gauntlets()[2].gauntletID() == Gauntlet::Poison);

        expect(r.gauntlets()[0].levels()[0] == 27732941_i);
        expect(r.gauntlets()[0].levels()[1] == 28200611_i);
        expect(r.gauntlets()[0].levels()[2] == 27483789_i);
        expect(r.gauntlets()[0].levels()[3] == 28225110_i);
        expect(r.gauntlets()[0].levels()[4] == 27448202_i);

        expect(r.gauntlets()[1].levels()[0] == 20635816_i);
        expect(r.gauntlets()[1].levels()[1] == 28151870_i);
        expect(r.gauntlets()[1].levels()[2] == 25969464_i);
        expect(r.gauntlets()[1].levels()[3] == 24302376_i);
        expect(r.gauntlets()[1].levels()[4] == 27399722_i);
    };

    "getGJUserInfo20.php"_test = [](){
        auto str = getResponseFromJson<getGJUserInfo20>();
        auto r = *rrp::rrp<rrp::v22::getGJUserInfo20>(str);
        //log_glaze(r);

        expect(r.user.userName() == "meluwudy");
        expect(r.user.userID() == 3935672_i);
        expect(r.user.secretCoins() == 148_i);
        expect(r.user.accBird() == 83_i);
        expect(r.user.youTube() == "UCZoN2WLAooS6uhREa9Cgpwg");
        
        expect(r.user.beatenDemons().easy == 143_i);
        expect(r.user.beatenDemons().medium == 67_i);
        expect(r.user.beatenDemons().hard == 56_i);
        expect(r.user.beatenDemons().insane == 112_i);
        expect(r.user.beatenDemons().extreme == 56_i);
        expect(r.user.beatenDemons().easyPlatformer == 1_i);
        expect(r.user.beatenDemons().mediumPlatformer == 1_i);
        expect(r.user.beatenDemons().hardPlatformer == 2_i);
        expect(r.user.beatenDemons().insanePlatformer == 1_i);
        expect(r.user.beatenDemons().extremePlatformer == 0_i);
        expect(r.user.beatenDemons().weekly == 21_i);
        expect(r.user.beatenDemons().gauntlet == 14_i);
    };

    "getGJDailyLevel.php"_test = [](){
        auto str = getResponseFromJson<getGJDailyLevel>();
        auto r = *rrp::rrp<rrp::v22::getGJDailyLevel>(str);
        //log_glaze(r);

        expect(r.levelIndex == 2959_i);
        expect(r.secondsLeft == 19186_i);
    };

    "downloadGJLevel22.php"_test = [](){
        auto str = getResponseFromJson<downloadGJLevel22>();
        auto r = *rrp::rrp<rrp::v22::downloadGJLevel22>(str);
        //log_glaze(r);
        
        expect(r.level.levelID() == 116370497_i);
    };
    "getGJRewards.php"_test = [](){
        auto str = getResponseFromJson<getGJRewards>();
        auto r = *rrp::rrp<v22::getGJRewards>(str);
        //log_glaze(r);

        expect(r.data.randomString == "LSxDq");
        expect(r.data.userID == 4460760_i);
        expect(r.data.smallChestReward.orbs == 40_i);
        expect(r.data.smallChestReward.diamonds == 4_i);
    };

    "getGJScores20.php"_test = [](){
        auto str = getResponseFromJson<getGJScores20>();

        auto r = *rrp::rrp<v22::getGJScores20>(str);
        //log_glaze(r);

        expect(r.users()[0].userName() == "xMiguel007"); 
        expect(r.users()[0].userID() == 2866103_i);
        expect(r.users()[0].secretCoins() == 149_i);

        expect(r.users()[1].userName() == "shaggy23");
        expect(r.users()[1].userID() == 1995959_i);
        expect(r.users()[1].secretCoins() == 149_i);
    };

    "getGJMapPacks21.php"_test = [](){
        auto str = getResponseFromJson<getGJMapPacks21>();
        auto r = *rrp::rrp<v22::getGJMapPacks21>(str);
        //log_glaze(r);

        expect(r.mappacks()[0].name() == "Cyclone Pack");
        expect(r.mappacks()[0].textColor().r == 255);
    };

    "getGJAccountComments"_test = [](){
        auto str = getResponseFromJson<getGJAccountComments20>();

        auto r = *rrp::rrp<v22::getGJAccountComments20>("2~T2ggOGsgc3RhcnMgbmljZQ==~4~47~9~2 years~6~1808699|2~NzUwMCBzdGFycyBjOg==~4~10~9~2 years~6~1803945|2~SSBiZWF0IDYgaW5zYW5lIGRlbW9ucyBpbiAyNCBob3VycyBsbWFvOiBOZWNyb3BvbGlzLCBUaGUgQ2F2ZXJucyBJSSwgRWxlbWVudHMgWCwgWCBBZHZlbnR1cmUsIFNhZGlzbSwgYW5kIEJsYXN0ZXIgYzo=~4~23~9~3 years~6~1793260|2~L1wvXC9cIDwz~4~8~9~3 years~6~1785414|2~U2VudCBmcm9tIGlPUyBTaG9ydGN1dHMh~4~11~9~4 years~6~1776426|2~VGhpcyBjb21tZW50IHdhcyB1cGxvYWRlZCBmb3IgdGhlIEdEIERvY3Mh~4~7~9~4 years~6~1772719|2~VGhlIHRyaWxvZ3kgaGFzIGJlZW4gY29tcGxldGVkLi4uR0cgQWZ0ZXJtYXRoIQ==~4~8~9~4 years~6~1766450|2~Im93byIgLSBGb3VuZG15YmFsbA==~4~4~9~4 years~6~1766338|2~NTAwMCBzdGFycyE=~4~12~9~4 years~6~1756926|2~Qmxvb2RiYXRoIEdHISEh~4~25~9~5 years~6~1745624#74:0:10");
        expect(r.comments()[0].likes() == 47_i);
        expect(r.comments()[0].age() == "2 years");
        expect(r.comments()[0].messageID() == 1808699_i);
        expect(r.comments()[0].comment() == "Oh 8k stars nice");

        expect(r.comments()[1].likes() == 10_i);
        expect(r.comments()[1].messageID() == 1803945_i);

        
        
        //log_glaze(r);
    };

    "getGJComments"_test = [](){
        auto str = getResponseFromJson<getGJComments21>();
        auto r = *rrp::rrp<v22::getGJComments21>(str);
        expect(r.comments()[0].comment.comment() == "74 att whatt");
        expect(r.comments()[0].comment.authorAccountID() == 210153877_i);
        expect(r.comments()[0].user.userName() == "dooblom");
        expect(r.comments()[0].user.iconID() == 91_i);
        expect(r.comments()[0].comment.comment() == "74 att whatt");

        expect(r.comments()[1].comment.comment() == "AAAAAAAAAA");
        expect(r.comments()[1].comment.authorAccountID() == 267641474_i);
        expect(r.comments()[1].user.userName() == "CaAlexDa");
        expect(r.comments()[1].user.iconID() == 26_i);

        //log_glaze(r);
    };
    
    "getGJSongInfo"_test = [](){
        auto str = getResponseFromJson<getGJSongInfo>();
        auto r = *rrp::rrp<v22::getGJSongInfo>(str);
        //log_glaze(r);
        expect(r.song.songID() == 10012354_i);
        expect(r.song.name() == "Always Be");
        expect(r.song.artistID() == 10003105_i);
        expect(r.song.artistName() == "Netrum");
        expect(r.song.sizeInMB() == 3.27f);
        expect(r.song.downloadLink() == "CUSTOMURL");
        expect(r.song.nongEnum() == 1_i);

        expect(r.song.extraArtistsIDs()[0] == 10003799_i);
        expect(r.song.extraArtistsIDs()[1] == 10003800_i);

    };

    "dynamic_test"_test = [](){
        std::string x = "0:1:2";
        PageInfo res = *rrp::rrp<PageInfo>(x);

        expect(res.total == 0_i);
        expect(res.offset == 1_i);
        expect(res.amount == 2_i);
    };

    "uploadGJLevel21"_test = [](){
        auto res = rrp::rrp<uploadGJLevel21>("-1");

        expect(res.has_value());
        expect(res->response == -1_i);

        res = rrp::rrp<uploadGJLevel21>("116368054");


        expect(res.has_value());
        expect(res->response == 116368054_i);
    };

    "getGJMessages20"_test = [](){
        auto str = getResponseFromJson<getGJMessages20>();
        auto res = *rrp::rrp<getGJMessages20>(str);
        
        expect(res.messages()[0].title() == "asdf");
        expect(res.messages()[0].age() == "1 month");
        expect(res.messages()[0].userName() == "RayDeeUx");

        //log_glaze(res);
    };

    "downloadGJMessage20"_test = [](){
        auto str = getResponseFromJson<downloadGJMessage20>();

        auto res = rrp::rrp<downloadGJMessage20>(str);
        
        expect(res.has_value());

        expect(res->message.messageID() == 89220349_i);
        expect(res->message.accountID() == 1941705_i);
        expect(res->message.title() == "asdf");
        expect(res->message.messageContent() == "foobar");
        //log_glaze(*res);
    };

    "getGJLevelScores211.php"_test = [](){
        auto str = getResponseFromJson<getGJLevelScores211>();
        auto res = rrp::rrp<getGJLevelScores211>(str);

        expect(res.has_value());
        expect(res->scores()[0].userName() == "donutsteel");
    };




}