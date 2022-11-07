#pragma once

class IOperation {
public:
	float range;
	float executeTime;
	int targetNumber;
	string opType;
	string opTargetType;

public:
	virtual void OnExecute() {};
	virtual void OnEnd() {};
	virtual void OnTick() {};
};