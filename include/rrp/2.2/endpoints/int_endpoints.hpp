#pragma once

#include <optional>
#include <rrp/rrp.hpp>

namespace rrp::v22
{

#define RRP_INT_ENDPOINT(T) struct T : SimpleIntResponseBase<T>{};

//ID of the level
RRP_INT_ENDPOINT(uploadGJLevel21)
RRP_INT_ENDPOINT(uploadGJLevelList)


//ID of the comment
RRP_INT_ENDPOINT(uploadGJComment21)
RRP_INT_ENDPOINT(uploadGJAccComment20)

//player id
RRP_INT_ENDPOINT(updateGJUserScore22)


RRP_INT_ENDPOINT(rateGJStars211)
RRP_INT_ENDPOINT(deleteGJLevelUser20)
RRP_INT_ENDPOINT(suggestGJStars20)
RRP_INT_ENDPOINT(rateGJDemon21)
RRP_INT_ENDPOINT(uploadGJMessage20)
RRP_INT_ENDPOINT(deleteGJMessages20)

RRP_INT_ENDPOINT(deleteGJComment20)
RRP_INT_ENDPOINT(deleteGJAccComment20)
RRP_INT_ENDPOINT(deleteGJLevelList)

RRP_INT_ENDPOINT(uploadFriendRequest20)
RRP_INT_ENDPOINT(deleteGJFriendRequests20)
RRP_INT_ENDPOINT(acceptGJFriendRequest20)
RRP_INT_ENDPOINT(readGJFriendRequest20)
RRP_INT_ENDPOINT(removeGJFriend20)
RRP_INT_ENDPOINT(blockGJUser20)
RRP_INT_ENDPOINT(unblockGJUser20)
RRP_INT_ENDPOINT(updateGJDesc20)
RRP_INT_ENDPOINT(likeGJItem211)
RRP_INT_ENDPOINT(requestUserAccess)
RRP_INT_ENDPOINT(reportGJLevel)
RRP_INT_ENDPOINT(updateGJAccSettings20)



}