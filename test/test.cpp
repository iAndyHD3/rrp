#include <filesystem>
#include <glaze/json/json_t.hpp>
#include <rrp/2.2/GetLevels21.hpp>
#include <rrp/2.2/getGJLevelLists.hpp>
#include <rrp/2.2/getGJGauntlets21.hpp>
#include <rrp/2.2/getGJUserInfo20.hpp>
#include <rrp/2.2/getGJDailyLevel.hpp>
#include <rrp/2.2/downloadGJLevel22.hpp>
#include <rrp/2.2/getGJRewards.hpp>
#include <rrp/2.2/getGJScores20.hpp>
#include <rrp/2.2/getGJMapPacks21.hpp>

#include "rrp/2.2/common.hpp"
#include "rrp/rrp.hpp"
#include "ut.hpp"

#include <glaze/glaze.hpp>
#include <rrp/rrp_glaze.hpp>

using namespace rrp;
using namespace boost::ut;

void printid(auto& ptr)
{
    std::cout << ptr.levelID() << "\n";
}

int fileCount = 0;

void log_glaze(const auto& response)
{
    std::string buffer = glz::write<glz::opts{.prettify = true}>(response).value_or("glaze error");
    std::cout
        << buffer
        << "\n------------------------\n";

    std::filesystem::path x = std::filesystem::temp_directory_path();
    std::filesystem::path file = x / std::string("rrp-test-" + std::to_string(fileCount) + ".json");
    std::ofstream f(file);
    f << buffer;
    std::cout << "SAVED TO: " << file.string() << std::endl;
    fileCount = fileCount + 1;
}

int main()
{

    static_assert(!Parsable<rrp::v22::GetGJLevels21>);
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
        auto r = rrp::rrp<rrp::v22::GetGJLevels21>("1:10565740:2:Bloodbath:5:3:6:503085:8:10:9:50:10:90849443:12:0:13:21:14:4285711:17:1:43:6:25::18:10:19:10330:42:0:45:24746:3:V2hvc2UgYmxvb2Qgd2lsbCBiZSBzcGlsdCBpbiB0aGUgQmxvb2RiYXRoPyBXaG8gd2lsbCB0aGUgdmljdG9ycyBiZT8gSG93IG1hbnkgd2lsbCBzdXJ2aXZlPyBHb29kIGx1Y2suLi4=:15:3:30:7679228:31:0:37:0:38:0:39:0:46:1:47:2:35:467339|1:21761387:2:Bloodbath Z:5:1:6:3277407:8:10:9:20:10:10030910:12:0:13:20:14:334046:17:1:43:4:25::18:10:19:17840:42:0:45:0:3:UmVtYWtlIG9mIEJCLCBidXQgU2hvcnRlciBhbmQgbXVjaCBlYXNpZXIgWEQgTW9yZSBvZiBhIGdhbWVwbGF5IGxldmVsISAgSnVzdCBhIGZ1biBlYXN5IGRlbW9uLiBWZXJpZmllZCBCeSBYaW9kYXplciEgRW5qb3kgOkQ=:15:3:30:0:31:0:37:3:38:1:39:10:46:1:47:2:35:223469|1:64968478:2:Bloodbath but no:5:1:6:19747356:8:10:9:50:10:2778887:12:0:13:21:14:171471:17::43:6:25::18:8:19:24992:42:0:45:23233:3:Qmxvb2RiYXRoLCBJdCdzIG5vdCBldmVuIHRoaXM=:15:3:30:0:31:0:37:0:38:1:39:8:46:1:47:2:35:706340|1:75795864:2:Bloodbath:5:3:6:12348083:8:10:9:40:10:473190:12:0:13:22:14:14499:17::43:5:25::18:7:19:25025:42:0:45:55985:3:VGhhbmtzIHRvIGV2ZXJ5b25lIGluIG15IGRpc2NvcmQgc2VydmVyIHRoYXQgY29udHJpYnV0ZWQ=:15:3:30:75393195:31:0:37:0:38:1:39:6:46:1:47:2:35:513064#503085:Riot:37415|3277407:Zyzyx:88354|12348083:KNOEPPEL:3009121|19747356:Texic:6152129#1~|~223469~|~2~|~ParagonX9 - HyperioxX~|~3~|~31~|~4~|~ParagonX9~|~5~|~3.77~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F223000%2F223469_ParagonX9___HyperioxX.mp3~|~7~|~~|~8~|~1~:~1~|~467339~|~2~|~At the Speed of Light~|~3~|~52~|~4~|~Dimrain47~|~5~|~9.56~|~6~|~~|~10~|~https%3A%2F%2Fgeometrydashcontent.b-cdn.net%2Fsongs%2F467339.mp3~|~7~|~~|~8~|~1~:~1~|~513064~|~2~|~EnV - Uprise~|~3~|~149~|~4~|~Envy~|~5~|~8.71~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F513000%2F513064_EnV---Uprise.mp3~|~7~|~UCaRqE7rKwJl1BvMRU4FFVJQ~|~8~|~1~:~1~|~706340~|~2~|~-At the Speed of Light- (8 bit Remix)~|~3~|~46724~|~4~|~ThaPredator~|~5~|~4.78~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F706000%2F706340_-At-the-Speed-of-Light--8-.mp3~|~7~|~~|~8~|~1#4:0:10#1664b8bb919b0822a4408752c37a9fb5f651f813");
    
        log_glaze(r);


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
            expect(r.levels()[1].levelName() == "Bloodbath Z") << r.levels()[1].levelName();
            expect(r.levels()[1].levelID() == 21761387_i);
            expect(r.levels()[1].customSongID() == 223469_i);
            expect(r.levels()[1].difficultyFace() == v22::DifficultyFace::MediumDemon);
            expect(r.levels()[1].rating() == v22::LevelRating::Featured);
        };

        "Songs"_test = [&](){
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
        auto r = rrp::rrp<GetLevelLists>("1:10834:2:my mcdonalds order:3:aSB3YWxrZWQgdG8gbWNkb25hbGRz:5:1:49:6061424:50:tricipital:10:237406:7:10:14:7845:19::51:78111123,80840474,20556675,71480069,51008389,26108947,59604964,190626,53898587,72443435,47499900,89638158,43758774,90640638,96282081,86742812:55:0:56:0:28:1703082168:29:0|1:4406:2:my mcdonalds order:3:aW0gYXQgdGhlIGRyaXZlIHRocnUgLy8gcGFydCAyIG91dCBub3cgYXQgNzIxMTQ=:5:7:49:17062290:50:GD2G:10:112863:7:2:14:4785:19::51:25147297,82785965,11171792,30261946,31496121,71189946,19716898,14456417,4050125,79412478,1442329,67287373,61350256:55:0:56:0:28:1703048969:29:1703631457|1:22325:2:My McDonalds Order:3:YmFuZ2VyIGxpc3QgaWNs:5:1:49:10722530:50:Jexamania:10:12774:7:9:14:275:19::51:25147297,83671207,46104803,72867858,65500565,16683338,32666588,25717922,84904479,92727112,69043485,4846999,58038680,67287373:55:0:56:0:28:1703125026:29:0|1:72114:2:my mcdonalds order 2:3:aSB0aGluayBoZSBsaWVkIGFib3V0IHRoZSBtYWNoaW5lIGJlaW5nIGJyb2tlbiAvLyB0aGUgc2VxdWVsIG5vIG9uZSBhc2tlZCBmb3IgdG8gbXkgbWNkb25hbGRzIG9yZGVy:5:3:49:17062290:50:GD2G:10:6990:7:2:14:189:19::51:25147297,65037091,88758014,59604964,67993675,59966737,56102262,97933043,2056444,85312317,91482208,58038680,46160451,75940156,95959832,81466909,68064189,61350256:55:0:56:0:28:1703631267:29:1703638822|1:16619:2:my mcdonalds order:3:SSBLTk9XIElUJ1MgQkFELCBUSEVSRSBXRVJFTidUIE1BTlkgT1BUSU9OUyE=:5:1:49:14542509:50:ZohMyGoodnessGD:10:3935:7:6:14:53:19::51:47499900,57410100,57474996,84904479,38557238,59157328,87981410,60001202,77367261,41551990,67287373:55:0:56:0:28:1703101621:29:0|1:33953:2:My mcdonalds order:3::5:3:49:14092610:50:RealGDVerse:10:883:7:2:14:41:19::51:82785965,11012303,38557238,18931295,11255719,61408958,26162113,72014001,42633903,13752832,69768064,49186967,77554979,22294605,70549760,66416136,50525701,89933948,37039661,58976282,6988127,86449162,3134009,87727825,82995551,73004601,57585857,82139948,95318968,69925593,1203245,69765381,50647963,67254591,14370474,96968200,93201502,92509265,65430141,56495221,76489404,91963243,41035356,62427241,68752244,69996378,26880009,7360312,79013891,65269818,76963460,88732322,11171792:55:0:56:0:28:1703206770:29:1703428545|1:12460:2:My McDonalds Order:3:bWNkb25hbA==:5:1:49:4236858:50:tim55:10:1703:7:4:14:38:19::51:82931130,69309640,56455492,36619357,55320441:55:0:56:0:28:1703087812:29:0|1:45077:2:My McDonalds Order:3:UmVhbA==:5:1:49:1839061:50:CreatorFreeze:10:1000:7:5:14:24:19::51:80840474,30963660,79412478,14456417,61293573,71971062,86929245,86742812,58038680:55:0:56:0:28:1703307069:29:0|1:29628:2:My mcdonalds order:3:YmFzZWQgb2ZmIGEgc3BvdGlmeSBwbGF5bGlzdCBvciBzb21ldGhpbmc=:5:3:49:10055542:50:RussianRobTop:10:1827:7:10:14:23:19::51:78111123,34889235,80840474,11171792,71480069,84904479,97589710,443669,4460853,72443435,97590104,13550658,2056444,86742812:55:0:56:0:28:1703180209:29:1703614964|1:68104:2:My McDonalds Order:3:TXkgcmVhbCBNY0RvbmFsZHMgb3JkZXIu:5:1:49:25642445:50:Anjixdude25z:10:691:7:9:14:17:19::51:78111123,59413153,12664426,97172976,87995257,85508683,89490621,72811779,10558915,9007089,84904479,27742076,61718673,27090448:55:0:56:0:28:1703571483:29:0#10532982:CreatorFreeze:1839061|14827098:tim55:4236858|15479163:tricipital:6061424|92900676:RussianRobTop:10055542|98535835:Jexamania:10722530|139957548:RealGDVerse:14092610|147859835:ZohMyGoodnessGD:14542509|25220930:GD2G:17062290|221186876:Anjixdude25z:25642445#9999:0:10#f5da5823d94bbe7208dd83a30ff427c7d88fdb99");
        log_glaze(r);
        
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
        auto r = rrp::rrp<rrp::v22::GetGauntlets>("1:1:3:27732941,28200611,27483789,28225110,27448202|1:2:3:20635816,28151870,25969464,24302376,27399722|1:3:3:28179535,29094196,29071134,26317634,12107595|1:4:3:26949498,26095850,27973097,27694897,26070995|1:5:3:18533341,28794068,28127292,4243988,28677296|1:6:3:28255647,27929950,16437345,28270854,29394058|1:7:3:25886024,4259126,26897899,7485599,19862531|1:8:3:18025697,23189196,27786218,27728679,25706351|1:9:3:40638411,32614529,31037168,40937291,35165900|1:10:3:37188385,35280911,37187779,36301959,36792656|1:11:3:37269362,29416734,36997718,39853981,39853458|1:12:3:27873500,34194741,34851342,36500807,39749578|1:13:3:43908596,41736289,42843431,44063088,44131636|1:14:3:38427291,38514054,36966088,38398923,36745142|1:15:3:44121158,43923301,43537990,33244195,35418014|1:16:3:105693414,86517581,92149907,95484955,106517747|1:18:3:37925002,68048356,110772842,15619194,90809996|1:21:3:57871639,82135935,81764520,80044470,92971865|1:22:3:110679874,110398067,108372523,70511594,82977900|1:29:3:75243812,57953054,102341639,97472588,85257263|1:34:3:91380905,68790607,75603568,57066554,49941534|1:35:3:75101593,62995779,93878047,71496773,58964029|1:36:3:68265721,41092171,99230232,96419926,78878411|1:37:3:92555035,94887416,85219434,89465157,82357008|1:38:3:41429267,66057230,113410989,58968008,66001175|1:40:3:39113837,64896078,95819007,56026863,94266027|1:41:3:96732638,70680001,69487890,89886591,8660411|1:42:3:82261821,97102482,28165621,103877520,108627188|1:43:3:80218929,95436164,64302902,65044525,66960655|1:46:3:83313115,83325036,83302544,83325083,81451870|1:47:3:83294687,83323867,83320529,83315343,83324930|1:48:3:83323273,83025300,83296274,83256789,83323659|1:49:3:89521875,90475659,90117883,88266256,88775556|1:50:3:90459731,90475597,90471222,90251922,90475473#d096d273a40aa7e302764919bcdb76c8abaa8e21");
        expect(r.gauntlets()[0].gauntletID() == 1_i);
        expect(r.gauntlets()[1].gauntletID() == 2_i);
        expect(r.gauntlets()[2].gauntletID() == 3_i);

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
        auto r = rrp::rrp<rrp::v22::GetUserInfo>("1:meluwudy:2:3935672:13:148:17:1068:10:12:11:15:51:10:3:9990:52:320:46:21504:4:476:8:1:18:0:19:0:50:0:20:UCZoN2WLAooS6uhREa9Cgpwg:21:82:22:17:23:113:24:83:25:85:26:24:28:1:43:2:48:2:53:26:54:3:30:29855:16:173831:31:0:44:logout:45:devexit:49:0:55:143,67,56,112,56,1,1,2,1,0,21,14:56:144,157,134,300,190,88,59,67:57:4,7,7,18,16,5,0:29:1");
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
        auto r = rrp::rrp<rrp::v22::GetDailyLevel>("2959|19186");
        expect(r.levelIndex == 2959_i);
        expect(r.secondsLeft == 19186_i);
    };

    "downloadGJLevel22.php"_test = [](){
        auto r = rrp::rrp<rrp::v22::DownloadGJLevel22>("1:128:2:1st level:3::4:H4sIAAAAAAAAC6WXUZLkIAiGL5StEgWV2qc5wxzAA8wV9vDbielEvumprtp9if3_AiIi0l-fpW8yNI08JNsoI5sNkTnkOUyyDkkpjTZkiO2fPtLoQ_7IOLRTfqst_6qt45dME_7SxC4zFd65kMeu-n829KX-Hr6nfnq3DfvRjfTeidtM_cHM9vUhZUv7YHOoc9Dt8Z2_22TOoe_DZ_ED5eM7DRwTH3p856ykOciWfssmW95yt61sYicsEqEGqCXCGqEHaPmCfYcWZ3uYrRJhXLe2AFuKMHrVbq8eE3nrhx_5CV0C3A804Iz5gnm9zdUdW4yYtBhQ6ZjvcWvZDRgHknAiSYEbDjABF-AaIl3EI84ZOPpXmDDMmCVlDn3FestJHwEt8_jyU79jvY71HOs51vMWsKYEjBxOS7r4QRwBqReWDGxPfOhL9E8L7BdckhJviWqMt6oBx4uiJsC4ohbzQWsChn8d8XLEywswLz1ufcrAuPcpxstEgBU4-mfFgGN8zCrw4l_ZiXYs-FhlL7NXNTq0NFkkSiOhJATE436AMBL5JhC8iRX4cqLi8td5-RX4drLOanAbOKtBuokZrnITTiLFfZ7Evc_T6HfCsMpKOIiz7BQQq4S9JJa9nKWJxOLYWawSiGVzs3ytRHspsdpoIOYzuagoQ6j1pcQ3GytRSTg2pzw5YwiNIZyv8ErwGM5nu0BlIWZBX2ycFX6RUEooJRolGiTmm79INOZYY46dbUKBykow-RvTsjGmnTHtjGlnCPsawryI-N3QxKLaUqwLTTKwAcei2rIAKzAaqsKOKhb9VipwbBqawj-Ffwr_0DQ1PGLNYtFvNQGz5UP8KuLX4J9jvw57jv163G_HI9fxyPXlkTt70NhF9hKb0q4a8XzFblx7xB32HE1uuuzt_jiaOEcT52jiHH2_l5gvrgk45ouj6XON8XOL8XP8OXCDfxX-4f-B15gv3hIw_GsxX7zFfPEO_66m9C_bF5V-dQ8AAA==:5:1:6:30144023:8:10:9:30:10:2864457:12:4:13:21:14:253052:17::43:0:25::18:0:19:0:42:0:45:208:15:2:30:128:31:0:28:11 years:29:7 years:35:0:36:0_46_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0:37:0:38:0:39:2:46::47::40::57::27:Aw==#30c4a15cfeb12f97de69d6bd0cc9478794e6c6c4#48e36e24b267df00a9c87aed127b4a9f020ac9c1");
        expect(r.level.levelID() == 128_i);
        expect(r.level.levelString() == "H4sIAAAAAAAAC6WXUZLkIAiGL5StEgWV2qc5wxzAA8wV9vDbielEvumprtp9if3_AiIi0l-fpW8yNI08JNsoI5sNkTnkOUyyDkkpjTZkiO2fPtLoQ_7IOLRTfqst_6qt45dME_7SxC4zFd65kMeu-n829KX-Hr6nfnq3DfvRjfTeidtM_cHM9vUhZUv7YHOoc9Dt8Z2_22TOoe_DZ_ED5eM7DRwTH3p856ykOciWfssmW95yt61sYicsEqEGqCXCGqEHaPmCfYcWZ3uYrRJhXLe2AFuKMHrVbq8eE3nrhx_5CV0C3A804Iz5gnm9zdUdW4yYtBhQ6ZjvcWvZDRgHknAiSYEbDjABF-AaIl3EI84ZOPpXmDDMmCVlDn3FestJHwEt8_jyU79jvY71HOs51vMWsKYEjBxOS7r4QRwBqReWDGxPfOhL9E8L7BdckhJviWqMt6oBx4uiJsC4ohbzQWsChn8d8XLEywswLz1ufcrAuPcpxstEgBU4-mfFgGN8zCrw4l_ZiXYs-FhlL7NXNTq0NFkkSiOhJATE436AMBL5JhC8iRX4cqLi8td5-RX4drLOanAbOKtBuokZrnITTiLFfZ7Evc_T6HfCsMpKOIiz7BQQq4S9JJa9nKWJxOLYWawSiGVzs3ytRHspsdpoIOYzuagoQ6j1pcQ3GytRSTg2pzw5YwiNIZyv8ErwGM5nu0BlIWZBX2ycFX6RUEooJRolGiTmm79INOZYY46dbUKBykow-RvTsjGmnTHtjGlnCPsawryI-N3QxKLaUqwLTTKwAcei2rIAKzAaqsKOKhb9VipwbBqawj-Ffwr_0DQ1PGLNYtFvNQGz5UP8KuLX4J9jvw57jv163G_HI9fxyPXlkTt70NhF9hKb0q4a8XzFblx7xB32HE1uuuzt_jiaOEcT52jiHH2_l5gvrgk45ouj6XON8XOL8XP8OXCDfxX-4f-B15gv3hIw_GsxX7zFfPEO_66m9C_bF5V-dQ8AAA==");
        expect(r.hash1 == "30c4a15cfeb12f97de69d6bd0cc9478794e6c6c4");
        expect(r.hash2 == "48e36e24b267df00a9c87aed127b4a9f020ac9c1");
    };
    "getGJRewards.php"_test = [](){
        auto r = rrp::rrp<v22::getGJRewards>("rEwZGeWpJfEMPDQUOAgIPAQIKBg4DCAAPX1deVFNfV14fDQFSDR9UWAdcH1NfV14fU19XXlFRDgMJBwRbCwkEDQEJDQIPCQsMAhkNHQgeBQMADgsBAwECAAAJHQkAGQgdCAgADwcCAg==|745d883ead4fc5888e3b7cac1fbfcdc72a85e2d5");
        //LSxDq:4460760:837202:ffffffff-88c5-aa6d-ffff-ffffcd72151b:1688850:0:40,4,0,0:1694:0:250,12,1,0:566:0 | C:/Users/User/Desktop/projects/cpp/rrp/include\rrp/2.2/getGJRewards.hpp:40
        expect(r.data.randomString == "LSxDq");
        expect(r.data.userID == 4460760_i);
        expect(r.data.smallChestReward.orbs == 40_i);
        expect(r.data.smallChestReward.diamonds == 4_i);
    };

    "getGJScores20.php"_test = [](){
        auto r = rrp::rrp<v22::getGJScores>("1:xMiguel007:2:2866103:13:149:17:7219:6:1:9:37:10:35:11:3:14:0:15:2:16:70846:3:65710:8:0:46:12879:4:1073|1:shaggy23:2:1995959:13:149:17:4321:6:2:9:51:10:39:11:29:14:0:15:2:16:2888:3:65595:8:21:46:11847:4:1115|1:Michigun:2:703929:13:149:17:12312:6:3:9:22:10:15:11:12:14:0:15:2:16:34499:3:61161:8:16:46:14600:4:997|1:Cool Dash:2:1148292:13:149:17:7026:6:4:9:37:10:20:11:17:14:0:15:2:16:4825:3:52931:8:0:46:14630:4:641|1:Kaernk:2:1282100:13:149:17:11908:6:5:9:51:10:18:11:12:14:0:15:2:16:118843:3:51821:8:0:46:17073:4:533|1:DeathHogz:2:1396933:13:149:17:5250:6:6:9:57:10:37:11:12:14:0:15:2:16:104119:3:51791:8:2:46:11948:4:435|1:Franchet:2:9576358:13:149:17:9840:6:7:9:30:10:15:11:12:14:0:15:2:16:1999478:3:51504:8:0:46:18616:4:670|1:Leksitoo:2:933105:13:149:17:4125:6:8:9:29:10:5:11:12:14:0:15:2:16:205:3:50530:8:14:46:13852:4:666|1:Superchat:2:2945295:13:149:17:5150:6:9:9:98:10:12:11:17:14:0:15:0:16:1098021:3:45706:8:2:46:14101:4:1201|1:Darky84:2:8513170:13:149:17:5864:6:10:9:37:10:12:11:25:14:0:15:2:16:1244088:3:44313:8:0:46:7444:4:1031|1:IvanNyan:2:14999317:13:149:17:5693:6:11:9:35:10:11:11:23:14:1:15:2:16:5148877:3:43785:8:0:46:6:4:563|1:GK NK 98:2:4803050:13:147:17:6491:6:12:9:2:10:12:11:23:14:6:15:2:16:890741:3:43163:8:2:46:14155:4:586|1:BonnieABoss:2:18158058:13:149:17:5572:6:13:9:105:10:15:11:3:14:0:15:2:16:5810059:3:43099:8:0:46:4743:4:778|1:FixTop100:2:18119007:13:149:17:801:6:14:9:1:10:0:11:3:14:0:15:0:16:5316700:3:43099:8:0:46:3559:4:323|1:TheRealAir:2:9035779:13:149:17:1270:6:15:9:35:10:12:11:25:14:0:15:2:16:2382846:3:42096:8:0:46:12808:4:665|1:XShadowWizardX:2:10670782:13:149:17:6097:6:16:9:85:10:12:11:7:14:0:15:2:16:1919857:3:41209:8:6:46:14083:4:540|1:CleanTop100:2:6552455:13:149:17:7111:6:17:9:30:10:7:11:12:14:0:15:2:16:2835706:3:40810:8:0:46:13243:4:871|1:xSuwako:2:14287615:13:149:17:2778:6:18:9:96:10:37:11:12:14:0:15:2:16:3984642:3:40695:8:0:46:11827:4:878|1:Civitrex2:2:14674984:13:149:17:7418:6:19:9:37:10:12:11:13:14:0:15:2:16:4156730:3:40576:8:0:46:13981:4:922|1:AdrianDlaCruz:2:16219796:13:148:17:2689:6:20:9:103:10:12:11:40:14:0:15:2:16:4771465:3:40286:8:0:46:4489:4:982|");
        expect(r.users()[0].userName() == "xMiguel007"); 
        expect(r.users()[0].userID() == 2866103_i);
        expect(r.users()[0].secretCoins() == 149_i);

        expect(r.users()[1].userName() == "shaggy23");
        expect(r.users()[1].userID() == 1995959_i);
        expect(r.users()[1].secretCoins() == 149_i);
    };

    "getGJMapPacks21.php"_test = [](){
        //auto r = rrp::rrp<v22::GetGJMapPacks21>("1:59:2:Cyclone Pack:3:1566116,946020,1100161:4:8:5:1:6:5:7:255,75,255:8:255,75,255|1:60:2:Colossus Pack:3:1350389,1215630,1724579:4:8:5:1:6:5:7:100,255,175:8:100,255,175|1:61:2:Diamond Pack:3:1267316,1670283,1205277:4:8:5:1:6:5:7:255,255,255:8:255,255,255|1:11:2:Chaos Pack:3:329929,188909,340602:4:9:5:1:6:5:7:255,125,0:8:255,125,0|1:44:2:Magma Pack:3:882417,884256,551979:4:9:5:1:6:5:7:255,100,50:8:255,100,50|1:62:2:Paradox Pack:3:1447246,1132530,1683722:4:9:5:1:6:5:7:50,255,75:8:50,255,75|1:63:2:Funky Pack:3:1728550,1799065,1311773:4:9:5:1:6:5:7:50,175,255:8:50,175,255|1:19:2:Remix Pack 4:3:341613,358750,369294:4:10:5:2:6:6:7:255,255,0:8:255,255,0|1:20:2:Demon Pack 1:3:70059,10109,135561:4:10:5:2:6:6:7:255,0,125:8:255,0,125|1:21:2:Demon Pack 2:3:57730,308891,102765:4:10:5:2:6:6:7:255,0,0:8:255,0,0#65:40:10#79c437d2cf75d2edf36a5094e0cc650c54440ba3");
        auto r = rrp::rrp<v22::GetGJMapPacks21>("1:59:2:Cyclone Pack:3:1566116,946020,1100161:4:8:5:1:6:5:7:255,75,255:8:255,75,255|1:60:2:Colossus Pack:3:1350389,1215630,1724579:4:8:5:1:6:5:7:100,255,175:8:100,255,175|1:61:2:Diamond Pack:3:1267316,1670283,1205277:4:8:5:1:6:5:7:255,255,255:8:255,255,255|1:11:2:Chaos Pack:3:329929,188909,340602:4:9:5:1:6:5:7:255,125,0:8:255,125,0|1:44:2:Magma Pack:3:882417,884256,551979:4:9:5:1:6:5:7:255,100,50:8:255,100,50|1:62:2:Paradox Pack:3:1447246,1132530,1683722:4:9:5:1:6:5:7:50,255,75:8:50,255,75|1:63:2:Funky Pack:3:1728550,1799065,1311773:4:9:5:1:6:5:7:50,175,255:8:50,175,255|1:19:2:Remix Pack 4:3:341613,358750,369294:4:10:5:2:6:6:7:255,255,0:8:255,255,0|1:20:2:Demon Pack 1:3:70059,10109,135561:4:10:5:2:6:6:7:255,0,125:8:255,0,125|1:21:2:Demon Pack 2:3:57730,308891,102765:4:10:5:2:6:6:7:255,0,0:8:255,0,0#65:40:10#79c437d2cf75d2edf36a5094e0cc650c54440ba3");
        expect(r.mappacks()[0].name() == "Cyclone Pack");
        expect(r.mappacks()[0].textColor().r == 255);
    };

}