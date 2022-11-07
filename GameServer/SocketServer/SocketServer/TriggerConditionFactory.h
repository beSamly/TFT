#pragma once
#include "ITriggerCondition.h"

class TriggerConditionFactory
{
private:
	std::map<string, ITriggerCondition> m_map;
public:
	TriggerConditionFactory();

public:
	ITriggerCondition create(string name, int threshold);
};

