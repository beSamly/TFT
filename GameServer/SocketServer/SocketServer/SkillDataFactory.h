#pragma once
#include "SkillData.h"
#include "TriggerConditionFactory.h"
#include "OperationFactory.h"

class SkillDataFactory
{

private:
	SkillDataFactory() { Init(); };
	void Init();
	std::map<int, SkillData> skillDataMap;

private:
	OperationFactory operationFactory;
	TriggerConditionFactory triggerConditionFactory;
	
	//ITriggerCondition GetTriggerConditon();
	//IOperation GetOperation();

public:
	static SkillDataFactory* GetInstance();
};

