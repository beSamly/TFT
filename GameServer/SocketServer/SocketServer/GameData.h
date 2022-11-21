#pragma once
#include "VectorPos.h"

class GameData
{
private:
    GameData();

public:
    static GameData* GetInstance();

private:
    list<VectorPos*> route;
    VectorPos spawnPosition;

public:
    VectorPos GetSpawnPosition();
    VectorPos GetDestPosition();
};