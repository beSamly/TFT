#pragma once
#include "TransformController.h"
#include "StatController.h"

class Champion
{
public:
    Champion(){};
    int star;
    void Update(float deltaTime);
    void SetBaseStat(ChampStatData statData);

private:
    TransformController transform;
    StatController stat;
    // SkillController
};
