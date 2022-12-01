#include "pch.h"
#include <fstream>
#include "ChampDataFactory.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void ChampDataFactory::LoadJsonData()
{
    LoadChampData();
    LoadChampStatData();
    LoadSkillData();
    LoadChampSkillData();
}

vector<ChampData> ChampDataFactory::GetChampPoolData() { return champDataVec; }

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

sptr<Champion> ChampDataFactory::CreateChampion(int champIndex)
{

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

void ChampDataFactory::LoadSkillData()
{
    std::ifstream f("./json/SkillData.json");

    json vectorData = json::parse(f);
    for (auto& d : vectorData)
    {
        SkillData data;

        data.skillIndex = d["Index"];
        data.aniDuration = d["AniDuration"];
        data.skillType = d["SkillType"];

        json triggerInfo = d["TriggerInfo"];
        data.triggerInfo.type = triggerInfo["Type"];
        data.triggerInfo.threshold = triggerInfo["Threshold"];
        data.triggerInfo.maxTriggerCount = triggerInfo["MaxTriggerCount"];

        json operationList = d["Operations"];
        for (auto& op : operationList)
        {
            // Operation base info
            Operation temp;
            temp.type = op["Star"];
            temp.value = op["Star"];
            temp.executeTime = op["Star"];
            temp.duration = op["Star"];

            // Operation target condition
            OperationTargetCondition tempTargetCondition;
            json targetCondition = op["TargetCondition"];
            tempTargetCondition.type = targetCondition["Type"];
            tempTargetCondition.targetNumber = targetCondition["TargetNumber"];
            tempTargetCondition.range = targetCondition["Range"];

            temp.condition = tempTargetCondition;

            data.operations.push_back(temp);
        }

        skillDataMap.emplace(data.skillIndex, data);
    }
}

void ChampDataFactory::LoadChampSkillData()
{
    std::ifstream f("./json/ChampSkillData.json");

    json vectorData = json::parse(f);
    for (auto& data : vectorData)
    {
        ChampSkillData temp;

        temp.championIndex = data["ChampIndex"];

        json baseAttackSkillIndex = data["BaseAttackSkillIndex"];
        json skillIndex = data["SkillIndex"];

        for (int skillIndex : baseAttackSkillIndex) {
            temp.baseAttackSkillIndex.push_back(skillIndex);
        }

        for (int skillIndex : skillIndex) {
            temp.skillIndex.push_back(skillIndex);
        }

        champSkillDataMap.emplace(temp.championIndex, temp);
    }
}
