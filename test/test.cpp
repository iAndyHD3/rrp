#include <rrp/2.2/GetLevels21.hpp>
#include "ut.hpp"

using namespace rrp;
using namespace boost::ut;

void printid(auto& ptr)
{
    std::cout << ptr.levelID() << "\n";
}

int main()
{
    static_assert(!Parsable<GJLevels21>);
    static_assert(Parsable<v22::CreatorObject<":">>);

    "essential_funcs"_test = [](){
        auto tokens = splitByDelimToMap("0:a:1:bb:2:ccc:3:dddd", ":");
        expect(tokens[0] == "a");
        expect(tokens[1] == "bb");
        expect(tokens[2] == "ccc");
        expect(tokens[3] == "dddd");
    };

    "2.2"_test = [](){
        auto r = rrp::rrp<GJLevels21>("1:10565740:2:Bloodbath:5:3:6:503085:8:10:9:50:10:90849443:12:0:13:21:14:4285711:17:1:43:6:25::18:10:19:10330:42:0:45:24746:3:V2hvc2UgYmxvb2Qgd2lsbCBiZSBzcGlsdCBpbiB0aGUgQmxvb2RiYXRoPyBXaG8gd2lsbCB0aGUgdmljdG9ycyBiZT8gSG93IG1hbnkgd2lsbCBzdXJ2aXZlPyBHb29kIGx1Y2suLi4=:15:3:30:7679228:31:0:37:0:38:0:39:0:46:1:47:2:35:467339|1:21761387:2:Bloodbath Z:5:1:6:3277407:8:10:9:20:10:10030910:12:0:13:20:14:334046:17:1:43:4:25::18:10:19:17840:42:0:45:0:3:UmVtYWtlIG9mIEJCLCBidXQgU2hvcnRlciBhbmQgbXVjaCBlYXNpZXIgWEQgTW9yZSBvZiBhIGdhbWVwbGF5IGxldmVsISAgSnVzdCBhIGZ1biBlYXN5IGRlbW9uLiBWZXJpZmllZCBCeSBYaW9kYXplciEgRW5qb3kgOkQ=:15:3:30:0:31:0:37:3:38:1:39:10:46:1:47:2:35:223469|1:64968478:2:Bloodbath but no:5:1:6:19747356:8:10:9:50:10:2778887:12:0:13:21:14:171471:17::43:6:25::18:8:19:24992:42:0:45:23233:3:Qmxvb2RiYXRoLCBJdCdzIG5vdCBldmVuIHRoaXM=:15:3:30:0:31:0:37:0:38:1:39:8:46:1:47:2:35:706340|1:75795864:2:Bloodbath:5:3:6:12348083:8:10:9:40:10:473190:12:0:13:22:14:14499:17::43:5:25::18:7:19:25025:42:0:45:55985:3:VGhhbmtzIHRvIGV2ZXJ5b25lIGluIG15IGRpc2NvcmQgc2VydmVyIHRoYXQgY29udHJpYnV0ZWQ=:15:3:30:75393195:31:0:37:0:38:1:39:6:46:1:47:2:35:513064#503085:Riot:37415|3277407:Zyzyx:88354|12348083:KNOEPPEL:3009121|19747356:Texic:6152129#1~|~223469~|~2~|~ParagonX9 - HyperioxX~|~3~|~31~|~4~|~ParagonX9~|~5~|~3.77~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F223000%2F223469_ParagonX9___HyperioxX.mp3~|~7~|~~|~8~|~1~:~1~|~467339~|~2~|~At the Speed of Light~|~3~|~52~|~4~|~Dimrain47~|~5~|~9.56~|~6~|~~|~10~|~https%3A%2F%2Fgeometrydashcontent.b-cdn.net%2Fsongs%2F467339.mp3~|~7~|~~|~8~|~1~:~1~|~513064~|~2~|~EnV - Uprise~|~3~|~149~|~4~|~Envy~|~5~|~8.71~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F513000%2F513064_EnV---Uprise.mp3~|~7~|~UCaRqE7rKwJl1BvMRU4FFVJQ~|~8~|~1~:~1~|~706340~|~2~|~-At the Speed of Light- (8 bit Remix)~|~3~|~46724~|~4~|~ThaPredator~|~5~|~4.78~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F706000%2F706340_-At-the-Speed-of-Light--8-.mp3~|~7~|~~|~8~|~1#4:0:10#1664b8bb919b0822a4408752c37a9fb5f651f813");


        "bloodbath"_test = [&](){

            printid(r.levels()[0]);

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
            r.levels()[1].levelName() == "Bloodbath Auto";
            r.levels()[1].levelID() == 10792915_i;
            r.levels()[1].customSongID() == 467339_i;
            r.levels()[1].difficultyFace() == v22::DifficultyFace::Hard;
            r.levels()[1].rating() == v22::LevelRating::None;


        };

    
    };
}