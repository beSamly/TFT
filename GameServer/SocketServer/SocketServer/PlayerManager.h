#pragma once
#include "Player.h"

class PlayerManager
{
public:
    PlayerManager();

private:
    USE_LOCK;
    uptr<map<int, sptr<Player>>> playerMap = make_unique<map<int, sptr<Player>>>();
    int tempPlayerId = 1;

public:
    void AddPlayer(sptr<Player> player);
    void Update();
};
