#pragma once
#include "pch.h"

struct ChampData
{
    int uid;
    int index;
    string displayName;
    int cost;
    int amount;
};

struct ChampStatData
{
    int star;
    int attackDamage;
    int abilityPower;
    int armor;
    int magicResistence;
    int attackSpeed;
    int moveSpeed;
};

class ChampDataFactory
{
private:
    vector<ChampData> champDataVec;
    map<int, vector<ChampStatData>> champStatDataMap;

public:
    ChampDataFactory(){};
    void LoadJsonData();
    vector<ChampData> GetChampData();
    ChampStatData GetStatData(int champIndex, int star);

private:
    void LoadChampData();
    void LoadChampStatData();
};
