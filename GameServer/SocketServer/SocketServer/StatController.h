#pragma once
#include "ChampDataFactory.h"

class StatController
{

private:

private:
    ChampStatData baseStatData;
    /*int currentHp;
    int currentMp;*/

public:
    StatController() {};
    void SetBaseStat(ChampStatData p_statData) { baseStatData = p_statData; }
};
