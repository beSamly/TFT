#pragma once
#include "GameHost.h"

class Player
{
public:
    int playerId;
    // Player(){};
    sptr<GameHost> currentGame;
};
