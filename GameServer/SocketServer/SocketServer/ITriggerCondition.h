#pragma once
class ITriggerCondition
{
public:
	string triggerType;
	int threshold;
public:
	virtual bool IsTriggered() { return false; };
};

