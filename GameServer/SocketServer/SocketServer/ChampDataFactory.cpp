#include "pch.h"
#include "ChampDataFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "SkillData.h"

using json = nlohmann::json;

void ChampDataFactory::LoadJsonData()
{
    LoadChampData();
    LoadChampStatData();
}

ChampStatData ChampDataFactory::GetStatData(int champIndex, int star)
{
    if (champStatDataMap.find(champIndex) != champStatDataMap.end())
    {
        vector<ChampStatData>& vec = champStatDataMap[champIndex];

        for (ChampStatData& data : vec)
        {
            if (data.star == star)
            {
                return data;
            }
        }
    }
}

void ChampDataFactory::LoadChampData()
{
    std::ifstream f("./json/ChampData.json");

    json vectorData = json::parse(f);
    for (auto& d : vectorData)
    {
        ChampData temp;
        temp.index = d["Index"];
        temp.displayName = d["DisplayName"];
        temp.cost = d["Cost"];
        temp.amount = d["Amount"];

        champDataVec.push_back(temp);
    }
}

void ChampDataFactory::LoadChampStatData()
{
    std::ifstream f("./json/ChampStatData.json");

    json vectorData = json::parse(f);
    for (auto& d : vectorData)
    {
        int champIndex = d["ChampIndex"];
        json statList = d["StatList"];

        vector<ChampStatData> vec;

        for (auto& stat : statList)
        {
            ChampStatData temp;

            // Operation op;
            temp.star = stat["Star"];
            temp.attackDamage = stat["AttackDamage"];
            temp.abilityPower = stat["AbilityPower"];
            temp.armor = stat["Armor"];
            temp.magicResistence = stat["MagicResistence"];
            temp.attackSpeed = stat["AttackSpeed"];
            temp.moveSpeed = stat["MoveSpeed"];

            vec.push_back(temp);
        }

        champStatDataMap.emplace(champIndex, vec);
    }
}
