#pragma once
#include "SkillData.h"
#include "TriggerConditionFactory.h"
#include "OperationFactory.h"

class SkillDataFactory
{
public:
	SkillDataFactory() { Init(); };

private:
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

