#pragma once
#include "ClientSession.h"

class MatchWaitPlayer
{

public:
    MatchWaitPlayer();
    wptr<ClientSession> client;
};
