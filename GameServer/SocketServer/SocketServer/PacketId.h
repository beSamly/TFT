#pragma once

namespace PacketId
{

enum Prefix : uint16
{
    AUTH = 1,
    MATCH,
    IN_GAME,
    DEBUG
};

enum Auth : uint16
{
    LOGIN_REQ = 1,
    LOGIN_RES,
};

enum Match : uint16
{
    AI_MATCH_REQ = 1,
    AI_MATCH_RES,
    MATCH_REQ,
    MATCH_RES,
};

enum InGame : uint16
{
    BUY = 1
};

enum Debug : uint16
{
    CREATE_DEBUG_MODE_HOST_REQ = 1
};
} // namespace PacketId
