#include "pch.h"
#include "SkillDataFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "ChampRelatedStruct.h"

using json = nlohmann::json;

SkillDataFactory* SkillDataFactory::GetInstance()
{
	static SkillDataFactory* instance = new SkillDataFactory();
	return instance;
}

void SkillDataFactory::Init()
{
	std::ifstream f("./json/SkillData.json");

	//json vectorData = json::parse(f);
	//for (auto& d : vectorData) {
	//	int index = d["Index"];
	//	int coolTime = d["CoolTime"];
	//	int duration = d["Duration"];
	//	json vectorOperation = d["Operation"];

	//	SkillData temp;
	//	temp.index = index;
	//	temp.coolTime = coolTime;

	//	/* TriggerCondition 추가 */
	//	json triggerCondition = d["TriggerCondition"];
	//	string triggerType = triggerCondition["TriggerType"];
	//	int triggerValue = triggerCondition["TriggerValue"];
	//	temp.triggerCondition = triggerConditionFactory.create(triggerType, triggerValue);

	//	/* Operation 추가 */
	//	for (auto& operation : vectorOperation) {
	//		//Operation op;
	//		int executeTime = operation["ExecuteTime"];
	//	}


	//	skillDataMap.insert(make_pair(temp.index, temp));
	//}
}
