#include "pch.h"
#include "TriggerConditionFactory.h"
#include "TCNone.h"

TriggerConditionFactory::TriggerConditionFactory()
{
	m_map.insert(make_pair(TriggerType::NONE, TCNone()));
}

ITriggerCondition TriggerConditionFactory::create(string name, int threshold)
{
	auto iter = m_map.find(name);
	ITriggerCondition instance = iter->second;
	instance.triggerType = name;
	instance.threshold = threshold;

	return instance;
}
