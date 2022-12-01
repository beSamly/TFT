#pragma once
#include "pch.h"
#include "ChampRelatedStruct.h"
#include "Champion.h"

class ChampDataFactory
{
private:
    vector<ChampData> champDataVec;
    map<int, vector<ChampStatData>> champStatDataMap;
    map<int, vector<ChampSkillData>> champSkillDataMap;
    map<int, vector<SkillData>> skillDataMap;

public:
    ChampDataFactory() {};
    void LoadJsonData();
    vector<ChampData> GetChampPoolData();
    ChampStatData GetStatData(int champIndex, int star);
    sptr<Champion> CreateChampion(int champIndex);

private:
    void LoadChampData();
    void LoadChampStatData();
    void LoadSkillData();
    void LoadChampSkillData();
};
