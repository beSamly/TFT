#pragma once

namespace PacketId
{
    enum Prefix : int
    {
        AUTH = 1,
        MATCH,
        IN_GAME,
        DEBUG
    };

    enum Auth : int
    {
        LOGIN_REQ = 1,
        LOGIN_RES,
    };

    enum Match : int
    {
        AI_MATCH_REQ = 1,
        AI_MATCH_RES,
        MATCH_REQ,
        MATCH_RES,
    };

    enum InGame : int
    {
        BUY = 1
    };

    enum Debug : int
    {
        CREATE_DEBUG_MODE_HOST_REQ = 1
    };
} // namespace PacketId
