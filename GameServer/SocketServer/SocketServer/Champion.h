#pragma once
#include "ClientSession.h"

class Champion
{
private:
    // TransformController
    // StatController
    // SkillController

public:
    Champion(){};
    int star;
    void Update(float deltaTime);

    void SetBaseStat(ChampStatData statData);
};
