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
        LOGOUT_REQ,
    };

    enum Match : int
    {
        MATCH_REQ = 1,
        MATCH_REQ_RES,
        PENDING_MATCH_CREATED_SEND,
        PENDING_MATCH_CANCELED_SEND,
        MATCH_ACCEPT_REQ
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
