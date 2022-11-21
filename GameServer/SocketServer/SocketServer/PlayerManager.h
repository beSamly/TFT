#pragma once

class PlayerManager
{
public:
    PlayerManager();

private:
    USE_LOCK;
    uptr<map<int32, sptr<Player>>> playerMap = make_unique<Map<int32, sptr<Player>>>();
    int tempPlayerId = 1;

public:
    void AddPlayer(sptr<Player> player);
    void Update();
};
