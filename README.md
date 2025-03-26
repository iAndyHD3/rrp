# rrp

Robtop response parser using modern C++

## Why?

The Geometry Dash web API has a very original way (to say it lightly) to format responses. The data is usually concatenated together and separated using specific delimiters. Parsing this manually is a complete nightmare in any serious big codebase. 

This library eases that pain by not only parsing all responses into sane structs, but doing so in a simple way that requires pretty much no boilerplate and that is easy to update, if the response data were to change in a future version.

## Usage

Parsing any response is as simple as choosing the correct type and passing it to the `rrp` function
```cpp
//hardcode the response for an example
std::string response = "1:10565740:2:Bloodbath:5:3:6:503085:8:10:9:50:10:90849443:12:0:13:21:14:4285711:17:1:43:6:25::18:10:19:10330:42:0:45:24746:3:V2hvc2UgYmxvb2Qgd2lsbCBiZSBzcGlsdCBpbiB0aGUgQmxvb2RiYXRoPyBXaG8gd2lsbCB0aGUgdmljdG9ycyBiZT8gSG93IG1hbnkgd2lsbCBzdXJ2aXZlPyBHb29kIGx1Y2suLi4=:15:3:30:7679228:31:0:37:0:38:0:39:0:46:1:47:2:35:467339|1:21761387:2:Bloodbath Z:5:1:6:3277407:8:10:9:20:10:10030910:12:0:13:20:14:334046:17:1:43:4:25::18:10:19:17840:42:0:45:0:3:UmVtYWtlIG9mIEJCLCBidXQgU2hvcnRlciBhbmQgbXVjaCBlYXNpZXIgWEQgTW9yZSBvZiBhIGdhbWVwbGF5IGxldmVsISAgSnVzdCBhIGZ1biBlYXN5IGRlbW9uLiBWZXJpZmllZCBCeSBYaW9kYXplciEgRW5qb3kgOkQ=:15:3:30:0:31:0:37:3:38:1:39:10:46:1:47:2:35:223469|1:64968478:2:Bloodbath but no:5:1:6:19747356:8:10:9:50:10:2778887:12:0:13:21:14:171471:17::43:6:25::18:8:19:24992:42:0:45:23233:3:Qmxvb2RiYXRoLCBJdCdzIG5vdCBldmVuIHRoaXM=:15:3:30:0:31:0:37:0:38:1:39:8:46:1:47:2:35:706340|1:75795864:2:Bloodbath:5:3:6:12348083:8:10:9:40:10:473190:12:0:13:22:14:14499:17::43:5:25::18:7:19:25025:42:0:45:55985:3:VGhhbmtzIHRvIGV2ZXJ5b25lIGluIG15IGRpc2NvcmQgc2VydmVyIHRoYXQgY29udHJpYnV0ZWQ=:15:3:30:75393195:31:0:37:0:38:1:39:6:46:1:47:2:35:513064#503085:Riot:37415|3277407:Zyzyx:88354|12348083:KNOEPPEL:3009121|19747356:Texic:6152129#1~|~223469~|~2~|~ParagonX9 - HyperioxX~|~3~|~31~|~4~|~ParagonX9~|~5~|~3.77~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F223000%2F223469_ParagonX9___HyperioxX.mp3~|~7~|~~|~8~|~1~:~1~|~467339~|~2~|~At the Speed of Light~|~3~|~52~|~4~|~Dimrain47~|~5~|~9.56~|~6~|~~|~10~|~https%3A%2F%2Fgeometrydashcontent.b-cdn.net%2Fsongs%2F467339.mp3~|~7~|~~|~8~|~1~:~1~|~513064~|~2~|~EnV - Uprise~|~3~|~149~|~4~|~Envy~|~5~|~8.71~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F513000%2F513064_EnV---Uprise.mp3~|~7~|~UCaRqE7rKwJl1BvMRU4FFVJQ~|~8~|~1~:~1~|~706340~|~2~|~-At the Speed of Light- (8 bit Remix)~|~3~|~46724~|~4~|~ThaPredator~|~5~|~4.78~|~6~|~~|~10~|~http%3A%2F%2Faudio.ngfiles.com%2F706000%2F706340_-At-the-Speed-of-Light--8-.mp3~|~7~|~~|~8~|~1#4:0:10#1664b8bb919b0822a4408752c37a9fb5f651f813";
auto res = rrp::rrp<rrp::v22::GetGJLevels21>(response);
```

**IMPORTANT**
The response structs use `std::string_view` almost everywhere to avoid extra allocations.
Make sure to use an extra variable for the response string and **never** do something like:
```cpp
auto res = rrp::rrp<rrp::v22::GetGJLevels21>(getResponse(params));
```

Be careful to only access std::string_view members while the original response string is alive.

## TODO:

- Fix crashes with malformed input


Missing endpoints:

- rateGJStars211.hpp
- deleteGJLevelUser20.hpp
- suggestGJStars20.hpp
- rateGJDemon21.hpp
- getGJLevelScoresPlat.hpp
- getGJTopArtists.hpp
- uploadGJMessage20.hpp
- deleteGJMessages20.hpp
- getGJCommentHistory.hpp
- uploadGJComment21.hpp
- uploadGJAccComment20.hpp
- deleteGJComment20.hpp
- deleteGJAccComment20.hpp
- getGJFriendRequests20.hpp
- uploadFriendRequest20.hpp
- deleteGJFriendRequests20.hpp
- acceptGJFriendRequest20.hpp
- readGJFriendRequest20.hpp
- removeGJFriend20.hpp
- blockGJUser20.hpp
- unblockGJUser20.hpp
- getGJUserList20.hpp
- updateGJDesc20.hpp
- likeGJItem211.hpp
- requestUserAccess.hpp
- getGJSecretReward.hpp
- getGJChallenges.hpp
- restoreGJItems.hpp
- reportGJLevel.hpp
- submitGJUserInfo.hpp
- uploadGJLevelList.hpp
- deleteGJLevelList.hpp
- updateGJUserScore22.hpp
- getCustomContentURL.hpp
- registerGJAccount.hpp
- loginGJAccount.hpp
- getAccountURL.hpp
- backupGJAccountNew.hpp
- syncGJAccountNew.hpp
- updateGJAccSettings20.hpp