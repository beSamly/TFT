#pragma once
#include "ChampDataFactory.h"

class StatController
{
private:
    ChampStatData statData;

public:
    StatController(){};
    void SetBaseStat(ChampStatData p_statData) { statData = p_statData; }
};
