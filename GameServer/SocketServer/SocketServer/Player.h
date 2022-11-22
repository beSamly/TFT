#pragma once
#include "GameHost.h"

class Player
{
public:
    int playerId;
    // Player(){};
    wptr<GameHost> currentGame;
};
